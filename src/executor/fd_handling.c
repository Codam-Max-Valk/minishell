#include "../../include/minishell.h"

void	reset_fd(t_shell *shell)
{
	dup2(shell->stdin_fd, STDIN_FILENO);
	dup2(shell->stdout_fd, STDOUT_FILENO);
}

void	reset_info_fd(t_info *info)
{
	if (info->fd_in > 0)
		close(info->fd_in);
	if (info->fd_out > 2)
		close(info->fd_out);
	if (info->pipe_in > 2)
		close(info->pipe_in);
	if (info->pipe_out > 2)
		close(info->pipe_out);
	info->fd_in = STDIN_FILENO;
	info->fd_out = STDOUT_FILENO;
	info->pipe_in = -1;
	info->pipe_out = -1;
}

void	set_redir_in(t_shell *shell, t_info *info, t_token *file)
{
	if (info->fd_in > 2)
		close(info->fd_in);
	if (file->tag == T_REDIRECT_IN)
		info->fd_in = open(file->content, O_RDONLY);
	else if (file->tag == T_HERE_DOC)
		info->fd_in = handle_here(file->content);
	if (info->fd_in == -1 && file != NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file->content, STDERR_FILENO);
		strerror(ENOENT);
	}
	// dup2(info->fd_in, STDIN_FILENO);
}

void	set_redir_out(t_shell *shell, t_info *info, t_token *file)
{
	if (info->fd_out > 2)
		close(info->fd_out);
	if (file->tag == T_APPEND)
		info->fd_out = open(file->content, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (file->tag == T_REDIRECT_OUT)
		info->fd_out = open(file->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (info->fd_out == -1 && file != NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file->content, STDERR_FILENO);
		strerror(errno);
	}
	// dup2(info->fd_out, STDOUT_FILENO);
}


