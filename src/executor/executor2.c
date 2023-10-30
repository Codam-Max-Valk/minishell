
#include "minishell.h"

void	error_exit(char *function, int error_num)
{
	perror(function);
	exit(error_num);
}

char	*create_here_file(int i)
{
	char	*tmp_file_name;
	char	*tmp_file_num;

	tmp_file_num = ft_itoa(i);
	if (tmp_file_num == NULL)
		return (NULL);
	tmp_file_name = ft_strjoin("/tmp/.heredoc_", tmp_file_num);
	free(tmp_file_num);
	if (!tmp_file_name)
		return (NULL);
	return (ft_strjoin_free(tmp_file_name, ".txt"));
}

int	handle_here(const char *delim, int i)
{
	char		*tmp_file;
	int			fd;
	char		*line;

	tmp_file = create_here_file(i);
	fd = open(tmp_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		error_exit("open", errno);
	while (1)
	{
		line = readline(">");
		if (line == NULL)
			error_exit("readline", errno);
		if (ft_strcmp(line, (char *)delim) == 0)
		{
			free(line);
			break ;
		}
		line = ft_strjoin_free(line, "\n");
		if (write(fd, line, ft_strlen(line)) == -1)
			error_exit("write", errno);
		free(line);
	}
	close(fd);
	return (open(tmp_file, O_RDONLY));
}


char	**parse_env(char **envp)
{
	char	**split_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
	split_path = ft_split(envp[i], ':');
	return (split_path);
}

char	*cmd_path(char **paths, char *cmd, int path_f)
{
	char	*full_cmd;
	char	*tmp;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (cmd);
	if (path_f == -1)
		return (NULL);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		full_cmd = ft_strjoin(tmp, cmd);
		free (tmp);
		if (access(full_cmd, F_OK) == 0)
			return (full_cmd);
		free (full_cmd);
		paths++;
	}
	return (NULL);
}

static void	set_fd_in(t_info *nxt, int fd_in)
{
	t_token	*tmp_tok = NULL;
	int		tmp_fd;
	static int		i = 0;

	if (nxt->inf == NULL)
		nxt->fd_in = dup(fd_in);
	else
	{
		tmp_fd = -1;
		nxt->fd_in = dup(fd_in);
		while (nxt->inf != NULL)
		{
			if (nxt->inf->tag == T_REDIRECT_IN)
				tmp_fd = open(nxt->inf->content, O_RDONLY);
			else if (nxt->inf->tag == T_HERE_DOC)
				tmp_fd = handle_here(nxt->inf->content, i);
			if (tmp_fd == -1)
				perror("infile not open");
			else
			{
				dup2(tmp_fd, nxt->fd_in);
				close(tmp_fd);
			}
			nxt->inf = nxt->inf->next;
			i++;
		}
	}
}

void	set_fd_out(t_info *cmd, int fd_out)
{
	t_token	*tmp_tok;
	int		tmp_fd;

	if (cmd->outf == NULL)
		cmd->fd_out = dup(fd_out);
	else
	{
		tmp_fd = -1;
		cmd->fd_out = dup(fd_out);
		while (cmd->outf != NULL)
		{
			if (cmd->outf->tag == T_APPEND)
				tmp_fd = open(cmd->outf->content, O_CREAT | O_RDWR | O_APPEND, 0644);
			else if (cmd->outf->tag == T_REDIRECT_OUT)
				tmp_fd = open(cmd->outf->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (tmp_fd == -1)
				perror("outfile not open");
			else 
			{
				dup2(tmp_fd, cmd->fd_out);
				close(tmp_fd);
			}
			cmd->outf = cmd->outf->next;
		}
	}
}

static void	child_exec(t_shell *shell, t_info *cmd, char *envp[])
{
	char	*cmd_p;

	close(cmd->pipe_fd[0]);
	if (cmd->fd_in != STDIN_FILENO)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
			error_exit("dup2-1", errno);
		close(cmd->fd_in);
	}		
	if (cmd->fd_out != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
			error_exit("dup2-2", errno);
		close(cmd->fd_out);
	}
	cmd_p = cmd_path(parse_env(envp), cmd->command[0], 1);
	if (cmd->is_builtin == true)
		exit(fire_builtin(shell, cmd->command));
	if (cmd_p != NULL)
	{
		if (execve(cmd_p, cmd->command, envp) < 0)
			error_exit("execve", errno);
	}
	ft_putstr_fd(cmd->command[0], 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

void	execute_command(t_shell *shell, t_info *cmd, char *envp[])
{
	pid_t	pid;
	char	*cmd_p;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		child_exec(shell, cmd, envp);
	}
	else
	{
		close(cmd->pipe_fd[0]);
		close(cmd->pipe_fd[1]);
		close(cmd->fd_in);
		close(cmd->fd_out);
		waitpid(pid, NULL, 0);
	}
}

void	exec_loop(t_shell *shell, t_info *info, char **envp)
{
	t_info	*cmd;

	if (info->command && !*info->command)
		return ;
	set_fd_in(info, STDIN_FILENO);
	while (info != NULL)
	{
		cmd = info;
		info = info->next;
		if (pipe(cmd->pipe_fd) == -1)
			error_exit("pipe", errno);
		if (info)
		{
			set_fd_in(info, cmd->pipe_fd[0]);
			set_fd_out(cmd, cmd->pipe_fd[1]);
		}
		else
		{
			set_fd_out(cmd, STDOUT_FILENO);
		}
		printf("outf:%d\n", cmd->fd_out);
		execute_command(shell, cmd, envp);
	}
}
