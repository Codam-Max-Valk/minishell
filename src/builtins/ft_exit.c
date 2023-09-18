#include "../../include/minishell.h"
#include "../../include/libft.h"

int	ft_exit(t_shell *shell, int argc, char **argv)
{
	shell->exited = 0;
	return (EXIT_SUCCESS);
}
