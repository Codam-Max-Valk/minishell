#include "../../include/minishell.h"
#include "../../include/libft.h"

int	ft_exit(t_shell *shell, int argc, char **argv)
{
	ft_printf("%s command brother\n", *argv);
	return (EXIT_SUCCESS);
}
