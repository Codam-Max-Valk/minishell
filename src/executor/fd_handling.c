#include "../../include/minishell.h"

static char	*create_here_file(int i)
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
		{
			close(fd);
			return (open(tmp_file, O_RDONLY));
		}
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
}


