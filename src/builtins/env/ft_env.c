#include "../../../include/libft.h"
#include "../../../include/minishell.h"

int	ft_env(t_shell *shell, int argc, char **argv)
{
	ft_printf("%s command brother\n", *argv);
	return (EXIT_SUCCESS);
}