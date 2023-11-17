
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
	if (pipe_fd < 1)
	{
		if (fd_red > 2)
		{
			dup2(fd_red, std);
			close(fd_red);
		}
	}
	else
	{
		dup2(pipe_fd, std);
		close(pipe_fd);
		if (fd_red > 2)
		{
			dup2(fd_red, std);
			close(fd_red);
		}
	}
}

int		execute_command(t_shell *shell, t_info *cmd, char *envp[])
{
	pid_t	pid;
	int		status;
	char	*cmd_p;

	
	cmd->pid = fork();
	if (cmd->pid == -1)
		return(EXIT_FAILURE);
	else if (cmd->pid == 0)
	{
		dup_child_fd(cmd, cmd->pipe_in, cmd->fd_in, STDIN_FILENO);
		dup_child_fd(cmd, cmd->pipe_out, cmd->fd_out, STDOUT_FILENO);
		child_exec(shell, cmd, envp);
		return (EXIT_SUCCESS);
	}
	else
	{
		reset_info_fd(cmd);
		return (EXIT_SUCCESS);
	}
}

void	open_redir_side(t_shell *shell, t_info *cmd, t_token *head, t_io side)
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

static void	single_command_exec(t_shell *shell, t_info *cmd, char **envp)
{
	open_redir_side(shell, cmd, cmd->inf, input);
	open_redir_side(shell, cmd, cmd->outf, output);
	if (does_builtin_exist(shell, *cmd->command) == true)
	{
		dup_child_fd(cmd, cmd->pipe_in, cmd->fd_in, STDIN_FILENO);
		dup_child_fd(cmd, cmd->pipe_out, cmd->fd_out, STDOUT_FILENO);
		fire_builtin(shell, cmd->command);
		reset_info_fd(cmd);
		reset_fd(shell);
	}
	else if (cmd->command)
	{
		execute_command(shell, cmd, envp);
		waitpid(cmd->pid, &shell->exit_code, 0);
		reset_info_fd(cmd);
		reset_fd(shell);
	}
}

void	exec_loop(t_shell *shell, t_info **info, char **envp)
{
	t_info	*nxt;
	t_info	*cmd;
	int		status;

	cmd = *info;
	// if (!cmd->command || !*cmd->command)
	// 	return ;
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
		open_redir_side(shell, cmd, cmd->inf, input);
		open_redir_side(shell, cmd, cmd->outf, output);
		execute_command(shell, cmd, envp);
		cmd = cmd->next;
		reset_fd(shell);
	}
	cmd = *info;
	while (cmd != NULL)
	{
		waitpid(cmd->pid, &status, 0);
		cmd = cmd->next;
	}
	reset_fd(shell);
}
