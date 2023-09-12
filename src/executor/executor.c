
#include "minishell.h"

typedef struct s_info
{
	char			**command;
	char			**append_out_file;
	char			**redirect_out_file;
	char			*heredoc;
	char			**redirect_in_file;
	struct s_info	*next;
	struct s_info	*prev;
}	t_info;

typedef	struct s_file_node
{
	char 		*file_name;
	t_tag 		type;
	t_file_node *next;
}	t_file_node;

size_t	count_command(t_info *infos)
{
	//gooi hier een count_cmd functie
	return (3);
}

void	execute_command_single(t_info *infos, char *envp[], int fd_in, int fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (fd_in != STDIN_FILENO)
		{
			if (dup2(fd_in, STDIN_FILENO) < 0)
				error_exit("dup2", errno);
			close(fd_in);
		}		
		if (fd_out != STDOUT_FILENO)
		{
			if (dup2(fd_out, STDOUT_FILENO) < 0)
				error_exit("dup2", errno);
			close(fd_out);
		}
		if (execve(infos->command[0], infos->command, envp) < 0)
			error_exit("execve", errno);
		ft_putstr_fd(infos->command[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	else
		waitpid(pid, NULL, 0);
}

void	set_start_fd(int *fd_in, int *fd_out, t_info *info)
{
	if (info->heredoc != NULL)
		handle_heredoc();
	if (info->redirect_in_file != NULL)
	{
		while (*info->redirect_in_file != NULL)
		{
			fd_in = open(info->redirect_in_file, O_RDONLY);
			if (fd_in == -1)
				perror("infile not open");
			info->redirect_in_file++;
		}
	}
	if (info->redirect_out_file != NULL)
	{
		while (*info->redirect_out_file != NULL)
		{
			fd_in = open(info->redirect_out_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
			fd_in = open(info->redirect_out_file, O_CREAT | O_RDWR | O_APPEND, 0644);
			if (fd_in == -1)
				perror("outfile not open");
			info->redirect_out_file++;
		}
	}
}

void	exec_loop(t_info *info)
{
	int		pipe_fd[2];
	int		fd_in;
	int		fd_out;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	while (info)
	{
		set_start_fd(&fd_in, &fd_out, info);
	}
}

int main()
{
	t_info a = calloc(1, sizeof(t_info));
	t_info
}