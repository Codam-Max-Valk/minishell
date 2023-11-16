
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

void	set_child_fd_in(t_info *cmd)
{
	if (cmd->pipe_in < 1)
	{
		// printf("no pipe in: cmd = %s\nfd_out:\t[%d]\nfd_in:\t[%d]\n", cmd->command[0], cmd->fd_out, cmd->fd_in);
		if (cmd->fd_in > 0)
		{
			dup2(cmd->fd_in, STDIN_FILENO);
			close(cmd->fd_in);
		}
	}
	else
	{
		// printf("yes pipe in: cmd = %s\nfd_out:\t[%d]\nfd_in:\t[%d]\npipe_in:\t[%d]\npipe_out:\t[%d]\n", cmd->command[0], cmd->fd_out, cmd->fd_in, cmd->pipe_in, cmd->pipe_out);
		if (cmd->fd_in > 0)
		{
			dup2(cmd->fd_in, STDIN_FILENO);
			close(cmd->fd_in);
			close(cmd->pipe_in);
		}
		else
		{
			dup2(cmd->pipe_in, STDIN_FILENO);
			close(cmd->pipe_in);
		}
	}
}

void	set_child_fd_out(t_info *cmd)
{
	if (cmd->pipe_out < 1)
	{
		// printf("no pipe out: cmd = %s\nfd_out:\t[%d]\nfd_in:\t[%d]\n", cmd->command[0], cmd->fd_out, cmd->fd_in);
		if (cmd->fd_out > 2)
		{
			dup2(cmd->fd_out, STDOUT_FILENO);
			close(cmd->fd_out);
		}
	}
	else
	{
		// printf("yes pipe out: cmd=%s\nfd_out:\t[%d]\nfd_in:\t[%d]\npipe_in:\t[%d]\npipe_out:\t[%d]\n", cmd->command[0], cmd->fd_out, cmd->fd_in, cmd->pipe_in, cmd->pipe_out);
		dup2(cmd->pipe_out, STDOUT_FILENO);
		close(cmd->pipe_out);
		if (cmd->fd_out > 2)
		{
			dup2(cmd->fd_out, STDOUT_FILENO);
			close(cmd->fd_out);
		}
	}
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
		set_child_fd_in(cmd);
		set_child_fd_out(cmd);
		child_exec(shell, cmd, envp);
		return (EXIT_SUCCESS);
	}
	else
	{
		// reset_info_fd(cmd);
		// waitpid(-1, &status, 0);
		// if(WIFEXITED(status))
		// 	return(WEXITSTATUS(status));
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
	int i = 0;

	cmd = *info;
	if (!cmd->command || !*cmd->command)
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
		// cmd->fd_in = STDIN_FILENO;
		// cmd->fd_out = STDOUT_FILENO;
		nxt = cmd->next;
		// printf("%p\n", nxt);
		if (nxt)
		{
			if (pipe(nxt->pipe_fd) == -1)
				error_exit("pipe", errno);
			cmd->pipe_out = nxt->pipe_fd[1];
			// dup2(cmd->pipe_out, cmd->fd_out);
			nxt->pipe_in = nxt->pipe_fd[0];
			// dup2(nxt->pipe_in, nxt->fd_in);
		}
		set_fd_side(shell, cmd, cmd->inf, input);
		set_fd_side(shell, cmd, cmd->outf, output);
		i++;
		execute_command(shell, cmd, envp);
		cmd = cmd->next;
	}
	// cmd = *info;

	// int status;

	// pid_t a[i + 1];

	// i = 0;
	// while (cmd != NULL)
	// {
	// 	a[i] = fork();
	// 	if (a[i] == 0)
	// 	cmd = cmd->next;
	// 	while (a[i] != 0)
	// 		waitpid(a[i], &status, 0);
	// }
	reset_fd(shell);
}
