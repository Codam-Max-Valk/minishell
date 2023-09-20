#include "../include/minishell.h"
#include "../include/libft.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

static int	open_or_create(void)
{
	int	fd;

	fd = 1000;
	if (access(HISTORY_FILE, F_OK) == -1)
		fd = open(HISTORY_FILE, O_CREAT | O_TRUNC | O_RDWR, 0600);
	if (access(HISTORY_FILE, F_OK | R_OK | W_OK) == 0)
		fd = open(HISTORY_FILE, O_RDWR | O_TRUNC);
	return (fd);

}

int	open_historyfile(void)
{
	int		fd;
	int		size;
	char	*content;

	fd = 0;
	size = 0;
	if (access(HISTORY_FILE, F_OK) == -1)
		fd = open(HISTORY_FILE, O_CREAT | O_TRUNC | O_RDWR, 0600);
	if (access(HISTORY_FILE, F_OK | R_OK | W_OK) >= 0)
		fd = open(HISTORY_FILE, O_RDWR);
	if (fd == -1)
		return (-1);
	content = get_next_line(fd);
	while (content)
	{
		add_history(content);
		size++;
		content = ft_strtrim(get_next_line(fd), "\n");
	}
	return (close(fd), fd);
}

//Add multiple checks
//1. Add write protection
//2. Add file descriptor protection
//3. Add history protection
void	ms_add_history(char	*str)
{
	int	fd;

	//fd = open_historyfile();
	//write(fd, str, ft_strlen(str));
	add_history(str);
}