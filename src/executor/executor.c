
#include "minishell.h"

int	handle_here()
{
	return (STDIN_FILENO);
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

void	error_exit(char *function, int error_num)
{
	perror(function);
	exit(error_num);
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

void	set_start_fd(t_info *info)
{
	t_file_node	*tmp;

	if (info->inf == NULL && info->fd_in == 0)
		info->fd_in = STDIN_FILENO;
	while (info->inf != NULL)
	{
		tmp = info->inf->content;
		if (tmp->type == T_REDIRECT_IN)
			info->fd_in = open(tmp->file_name, O_RDONLY);
		else if (tmp->type == T_HERE_DOC)
			info->fd_in = handle_here();
		if (info->fd_in == -1)
			perror("infile not open");
		info->inf = info->inf->next;
	}
	if (info->outf == NULL && info->fd_out == 0)
		info->fd_out = STDOUT_FILENO;
	while (info->outf != NULL)
	{
		tmp = info->outf->content;
		if (tmp->type == T_APPEND)
			info->fd_out = open(tmp->file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
		else if (tmp->type == T_REDIRECT_OUT)
			info->fd_out = open(tmp->file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (info->fd_out == -1)
			perror("outfile not open");
		info->outf = info->outf->next;
	}

}

void	execute_command(t_info *info, char *envp[])
{
	pid_t	pid;
	char	*cmd_p;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		set_start_fd(info);
		if (info->fd_in != STDIN_FILENO)
		{
			if (dup2(info->fd_in, STDIN_FILENO) < 0)
				error_exit("dup2-1", errno);
			close(info->fd_in);
		}		
		if (info->fd_out != STDOUT_FILENO)
		{
			if (dup2(info->fd_out, STDOUT_FILENO) < 0)
				error_exit("dup2-2", errno);
			close(info->fd_out);
		}
		cmd_p = cmd_path(parse_env(envp), info->command[0], 1);
		if (execve(cmd_p, info->command, envp) < 0)
			error_exit("execve", errno);
		exit(1);
	}
	else
	{
		waitpid(pid, NULL, 0);
		if (info->fd_out == info->pipe_fd[1])
			close(info->fd_out);
	}
}

void	exec_loop(t_info *info, char *envp[])
{
	t_info	*current_cmd;
	bool	has_p = false;

	while (info != NULL)
	{
		if (info->next)
			has_p = true;
		else
			has_p = false;
		current_cmd = info;
		info = info->next;
		if (has_p == true)
		{
			if (pipe(current_cmd->pipe_fd) == -1)
				error_exit("pipe", errno);
		}
		if (info != NULL)
		{
			current_cmd->fd_out = current_cmd->pipe_fd[1];
			info->fd_in = current_cmd->pipe_fd[0];
		}
		else
			current_cmd->fd_out = STDOUT_FILENO;
		execute_command(current_cmd, envp);
	}
}
