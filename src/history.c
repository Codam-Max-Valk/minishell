#include "../include/minishell.h"
#include "../include/libft.h"

static int	open_or_create(void)
{
	int	fd;

	fd = -1;
	//if (access(HISTORY_FILE, F_OK) == -1)
	//	fd = open(HISTORY_FILE, O_CREAT | O_TRUNC | O_RDWR | O_APPEND, 0600);
	//if (access(HISTORY_FILE, F_OK | R_OK | W_OK) == 0)
	//	fd = open(HISTORY_FILE, O_RDWR | O_APPEND);
	return (fd);
}

int	open_historyfile(void)
{
	int		fd;
	size_t	count;
	char	*content;

	fd = open_or_create();
	if (fd == -1)
		return (-1);
	content = "\0";
	count = 0;
	while (content)
	{
		content = get_next_line(fd);
		if (!content)
			return (0);
		add_history(content);
		free(content);
		count++;
	}
	printf("[History] Added %zu lines to history\n", count);
	return (close(fd), 1);
}

void	ms_add_history(char	*str)
{
	const int	fd = open_or_create();

	if (fd != -1)
	{
		ft_putstr_fd(str, fd);
		ft_putchar_fd('\n', fd);
		close(fd);
	}
	add_history(str);
}
