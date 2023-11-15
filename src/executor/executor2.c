
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

int	handle_here(const char *delim)
{
	char		*tmp_file;
	static int	i = 0;
	int			fd;
	char		*line;

	tmp_file = create_here_file(i++);
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

// static void	set_fd_in(t_info *nxt, int fd_in)
// {
// 	int				tmp_fd;
// 	static int		i = 0;
// 	t_token			*tmp_red;

// 	if (nxt->inf == NULL)
// 		nxt->fd_in = dup(fd_in);
// 	else
// 	{
// 		tmp_fd = -1;
// 		nxt->fd_in = dup(fd_in);
// 		tmp_red = nxt->inf;
// 		while (tmp_red != NULL)
// 		{
// 			if (tmp_red->tag == T_REDIRECT_IN)
// 				tmp_fd = open(tmp_red->content, O_RDONLY);
// 			else if (tmp_red->tag == T_HERE_DOC)
// 				tmp_fd = handle_here(tmp_red->content, i++);
// 			if (tmp_fd == -1)
// 				perror("infile not open");
// 			else 
// 			{
// 				dup2(tmp_fd, nxt->fd_in);
// 				close(tmp_fd);
// 			}
// 			tmp_red = tmp_red->next;
// 		}
// 	}
// }

// void	set_fd_out(t_info *cmd, int fd_out)
// {
// 	int		tmp_fd;
// 	t_token			*tmp_red;

// 	if (cmd->outf == NULL)
// 		cmd->fd_out = dup(fd_out);
// 	else
// 	{
// 		tmp_fd = -1;
// 		cmd->fd_out = dup(fd_out);
// 		tmp_red = cmd->outf;
// 		while (tmp_red != NULL)
// 		{
// 			if (tmp_red->tag == T_APPEND)
// 				tmp_fd = open(tmp_red->content, O_CREAT | O_RDWR | O_APPEND, 0644);
// 			else if (tmp_red->tag == T_REDIRECT_OUT)
// 				tmp_fd = open(tmp_red->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
// 			if (tmp_fd == -1)
// 				perror("outfile not open");
// 			else 
// 			{
// 				dup2(tmp_fd, cmd->fd_out);
// 				close(tmp_fd);
// 			}
// 			tmp_red = tmp_red->next;
// 		}
// 	}
// }

static void	child_exec(t_shell *shell, t_info *cmd, char *envp[])
{
	char	*cmd_p;
	char	**env_p;

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
		close(shell->pipe_fd[1]);
		child_exec(shell, cmd, envp);
		return (EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		reset_info_fd(cmd);
		if(WIFEXITED(status))
			return(WEXITSTATUS(status));
		return (EXIT_SUCCESS);
	}
}

int	single_command_exec(t_shell *shell, t_info *cmd, char **envp)
{
	if (does_builtin_exist(shell, *cmd->command) == true)
	{
		return (fire_builtin(shell, cmd->command));
	}
	else
	{
		return (execute_command(shell, cmd, envp));
	}
}

void	set_fd_side(t_shell *shell, t_info *cmd, t_token *head, t_io side)
{
	t_token	*tmp;

	tmp = head;
	if (tmp == NULL && cmd->pipe_out > 0 && side == output && cmd->next)
	{
		dup2(cmd->pipe_out, STDOUT_FILENO);
		return ;
	}
	if (tmp == NULL && cmd->pipe_in > 0 && side == input)
	{
		dup2(cmd->pipe_in, STDIN_FILENO);
		return ;
	}
	while (tmp)
	{
		if (side == input)
			set_redir_in(shell, cmd, tmp);
		else if (side == output)
			set_redir_out(shell, cmd, tmp);
		tmp = tmp->next;
	}
}

void	exec_loop(t_shell *shell, t_info **info, char **envp)
{
	t_info	*nxt;
	t_info	*cmd;

	cmd = *info;
	if (cmd->command && !*cmd->command)
		return ;
	if (cmd->next == NULL)
	{
		set_fd_side(shell, cmd, cmd->inf, input);
		set_fd_side(shell, cmd, cmd->outf, output);
		single_command_exec(shell, cmd, envp);
		reset_fd(shell);
		return ;
	}
	while (cmd != NULL)
	{
		nxt = cmd->next;
		if (pipe(shell->pipe_fd) == -1)
			error_exit("pipe", errno);
		cmd->pipe_out = shell->pipe_fd[1];
		if (nxt)
		{
			nxt->pipe_in = shell->pipe_fd[0];
		}
		set_fd_side(shell, cmd, cmd->inf, input);
		set_fd_side(shell, cmd, cmd->outf, output);
		execute_command(shell, cmd, envp);
		reset_fd(shell);
		cmd = cmd->next;
	}
}
