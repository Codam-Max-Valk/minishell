# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdbool.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_info
{
	char			**command;
	char			*heredoc;
	char			**append_out_file;
	char			**redirect_out_file;
	char			**redirect_in_file;
	// t_tag			tag;
	struct s_info	*next;
	struct s_info	*prev;
}	t_info;

size_t	count_command(t_info *infos)
{
	//gooi hier een count_cmd functie
	return (3);
}

void	execute_command(t_info *infos)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (infos->heredoc != NULL)	
			handle_heredoc();
	}
}

void	exec_loop(t_info *info)
{
	size_t	command_count;
	size_t	i;
	int		pipe_fd[2];

	command_count = count_command(info);
	// fd_in = STDIN_FILENO;
	// fd_out = -1;
	if (pipe(pipe_fd) == -1)
		exit(EXIT_FAILURE);
	while (i < command_count)
	{
		if (i == command_count - 1)
			fd_out = STDOUT_FILENO;
		else
			fd_out = -1;
	}
}

