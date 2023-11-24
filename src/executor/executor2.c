
#include "minishell.h"

void	error_exit(char *function, int error_num)
{
	perror(function);
	exit(error_num);
}

static void	child_exec(t_shell *shell, t_info *cmd, char *envp[])
{
	char	*cmd_p;
	char	**env_p;

	env_p = parse_env(envp);
	cmd_p = cmd_path(env_p, cmd->command[0], 1);
	if (does_builtin_exist(shell, *cmd->command))
	{
		fire_builtin(shell, cmd->command);
		child_cleanup(shell, cmd, cmd_p, env_p);
		exit(EXIT_SUCCESS);
	}
	if (cmd_p != NULL)
	{
		if (execve(cmd_p, cmd->command, envp) < 0)
			error_exit("execve", errno);
	}
	ft_putstr_fd(cmd->command[0], 2);
	ft_putendl_fd(": command not found", 2);
	child_cleanup(shell, cmd, cmd_p, env_p);
	exit(127);
}

void	dup_child_fd(t_info *cmd, int pipe_fd, int fd_red, int std)
{
	if (pipe_fd > 0)
	{
		dup2(pipe_fd, std);
		close(pipe_fd);
	}
	if (fd_red > 2)
	{
		dup2(fd_red, std);
		close(fd_red);
	}

}

void	open_redir(t_shell *shell, t_info *cmd, t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->tag == T_REDIRECT_IN || tmp->tag == T_HERE_DOC)
			set_redir_in(shell, cmd, tmp);
		else if (tmp->tag == T_APPEND || tmp->tag == T_REDIRECT_OUT)
			set_redir_out(shell, cmd, tmp);
		if (cmd->should_x == false)
			break ;
		tmp = tmp->next;
	}
}
void	execute_command(t_shell *shell, t_info *cmd, char *envp[])
{
	pid_t	pid;
	int		status;
	char	*cmd_p;

	if (!cmd->command || !*cmd->command)
		cmd->should_x = false;
	signal(SIGINT, child_sig_handle);
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		print_mini_err(shell, "fork", errno);
		shell->exit_code[0] = 1;
	}
	else if (cmd->pid == 0)
	{
		if (cmd->next)
			close(cmd->next->pipe_fd[0]);
		dup_child_fd(cmd, cmd->pipe_in, cmd->fd_in, STDIN_FILENO);
		dup_child_fd(cmd, cmd->pipe_out, cmd->fd_out, STDOUT_FILENO);
		if (cmd->should_x == true)
			child_exec(shell, cmd, envp);
		exit(shell->exit_code[0]);
	}
}

static void	single_command_exec(t_shell *shell, t_info *cmd, char **envp)
{
	int	status;

	status = 0;
	open_redir(shell, cmd, cmd->red);
	if (does_builtin_exist(shell, *cmd->command) == true && cmd->should_x == true)
	{
		dup_child_fd(cmd, cmd->pipe_in, cmd->fd_in, STDIN_FILENO);
		dup_child_fd(cmd, cmd->pipe_out, cmd->fd_out, STDOUT_FILENO);
		fire_builtin(shell, cmd->command);
	}
	else if (cmd->command && cmd->should_x == true)
	{
		execute_command(shell, cmd, envp);
		waitpid(cmd->pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_code[0] = WEXITSTATUS(status);
	}
	reset_info_fd(cmd);
	reset_fd(shell);
}

static void	wait_for_kids(t_shell *shell, t_info *info)
{
	int	status;

	while (info != NULL)
	{
		status = 0;
		waitpid(info->pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_code[0] = WEXITSTATUS(status);
		info = info->next;
	}
	reset_fd(shell);
}

void	exec_loop(t_shell *shell, t_info **info, char **envp)
{
	t_info	*nxt;
	t_info	*cmd;

	cmd = *info;
	if (cmd->next == NULL)
		return (single_command_exec(shell, cmd, envp));
	while (cmd != NULL)
	{
		nxt = cmd->next;
		if (nxt)
		{
			if (pipe(nxt->pipe_fd) == -1)
				error_exit("pipe", errno);
			cmd->pipe_out = nxt->pipe_fd[1];
			nxt->pipe_in = nxt->pipe_fd[0];
		}
		open_redir(shell, cmd, cmd->red);
		execute_command(shell, cmd, envp);
		if (nxt)
		{
			close(cmd->next->pipe_fd[1]);
			close(cmd->next->pipe_fd[0]);
		}
		cmd = cmd->next;
	}
	wait_for_kids(shell, *info);
}
