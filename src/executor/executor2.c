
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

static void	set_fd_in(t_info *nxt, int fd_in)
{
	int				tmp_fd;
	static int		i = 0;
	t_token			*tmp_red;

	if (nxt->inf == NULL)
		nxt->fd_in = dup(fd_in);
	else
	{
		tmp_fd = -1;
		nxt->fd_in = dup(fd_in);
		tmp_red = nxt->inf;
		while (tmp_red != NULL)
		{
			if (tmp_red->tag == T_REDIRECT_IN)
				tmp_fd = open(tmp_red->content, O_RDONLY);
			else if (tmp_red->tag == T_HERE_DOC)
				tmp_fd = handle_here(tmp_red->content, i++);
			if (tmp_fd == -1)
				perror("infile not open");
			else 
			{
				dup2(tmp_fd, nxt->fd_in);
				close(tmp_fd);
			}
			tmp_red = tmp_red->next;
		}
	}
}

void	set_fd_out(t_info *cmd, int fd_out)
{
	int		tmp_fd;
	t_token			*tmp_red;

	if (cmd->outf == NULL)
		cmd->fd_out = dup(fd_out);
	else
	{
		tmp_fd = -1;
		cmd->fd_out = dup(fd_out);
		tmp_red = cmd->outf;
		while (tmp_red != NULL)
		{
			if (tmp_red->tag == T_APPEND)
				tmp_fd = open(tmp_red->content, O_CREAT | O_RDWR | O_APPEND, 0644);
			else if (tmp_red->tag == T_REDIRECT_OUT)
				tmp_fd = open(tmp_red->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (tmp_fd == -1)
				perror("outfile not open");
			else 
			{
				dup2(tmp_fd, cmd->fd_out);
				close(tmp_fd);
			}
			tmp_red = tmp_red->next;
		}
	}
}

static void	child_exec(t_shell *shell, t_info *cmd, char *envp[])
{
	char	*cmd_p;
	char	**env_p;

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
	env_p = parse_env(envp);
	cmd_p = cmd_path(env_p, cmd->command[0], 1);
	if (cmd->is_builtin == true)
		exit(fire_builtin(shell, cmd->command));
	if (cmd_p != NULL)
	{
		if (execve(cmd_p, cmd->command, envp) < 0)
			error_exit("execve", errno);
	}
	ft_putstr_fd(cmd->command[0], 2);
	ft_putendl_fd(": command not found", 2);
	free_double_array(env_p);
	free(cmd_p);
	cleanup_base(shell);
	clean_info(&cmd);
	exit(127);
}

int		execute_command(t_shell *shell, t_info *cmd, char *envp[])
{
	pid_t	pid;
	int		status;
	char	*cmd_p;

	
	pid = fork();
	if (pid == -1)
		return(EXIT_FAILURE);
	else if (pid == 0)
	{
		close(cmd->pipe_fd[0]);
		return (child_exec(shell, cmd, envp), EXIT_SUCCESS);
	}
	else
	{
		close(cmd->pipe_fd[0]);
		close(cmd->pipe_fd[1]);
		close(cmd->fd_in);
		close(cmd->fd_out);
		waitpid(pid, &status, 0);
		if(WIFEXITED(status))
			return(WEXITSTATUS(status));
		return (EXIT_SUCCESS);
	}
}

void	exec_loop(t_shell *shell, t_info **info, char **envp)
{
	t_info	*nxt;
	t_info	*cmd;

	cmd = *info;
	if (cmd->command && !*cmd->command)
		return ;
	set_fd_in(cmd, STDIN_FILENO);
	set_fd_out(cmd, STDOUT_FILENO);
	if (cmd->next == NULL && does_builtin_exist(shell, *cmd->command) == true)
	{
		if (cmd->fd_out != STDOUT_FILENO)
		{
			if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
				error_exit("dup2-2", errno);
			close(cmd->fd_out);
		}
		fire_builtin(shell, cmd->command);
		close(cmd->fd_in);
		close(cmd->fd_out);
		return ;
	}
	while (cmd != NULL)
	{
		nxt = cmd;
		cmd = cmd->next;
		if (pipe(nxt->pipe_fd) == -1)
			error_exit("pipe", errno);
		if (cmd)
		{
			set_fd_in(cmd, nxt->pipe_fd[0]);
			set_fd_out(nxt, nxt->pipe_fd[1]);
		}
		else
			set_fd_out(nxt, STDOUT_FILENO);
		shell->exit_code = execute_command(shell, nxt, envp);
	}
}
