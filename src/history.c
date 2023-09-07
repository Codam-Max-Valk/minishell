#include "../include/minishell.h"
#include "../include/libft.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#define HISTORY_FILE "~/.minishell_history"

bool	initialize_history()
{
	int	fd;

	fd = open(HISTORY_FILE, O_RDONLY);
	if (access(HISTORY_FILE, F_OK | R_OK | W_OK))
		
	if (!fd)
		return (false); //History file failed to open...
}