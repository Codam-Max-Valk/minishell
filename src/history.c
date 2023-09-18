#include "../include/minishell.h"
#include "../include/libft.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#define HISTORY_FILE "~/.minishell_history"

int	open_historyfile(void)
{
	int	fd;

	if (access(HISTORY_FILE, F_OK))
		fd = open(HISTORY_FILE, O_CREAT | O_RDWR);
	if (access(HISTORY_FILE, R_OK | W_OK))
		fd = open(HISTORY_FILE, O_RDWR);
	if (!fd)
		return (-1); //History file failed to open...
	return (fd);
}

//Add multiple checks
//1. Add write protection
//2. Add file descriptor protection
//3. Add history protection
void	ms_add_history(char	*str)
{
	//int	fd;

	//fd = open_historyfile();
	//write(fd, str, ft_strlen(str));
	add_history(str);
}