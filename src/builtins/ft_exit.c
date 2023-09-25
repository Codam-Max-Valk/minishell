
#include "../../include/minishell.h"
#include "../../include/libft.h"

int	ft_exit(t_shell *shell, int argc, char **argv)
{
	return (shell->exited = 0);
}
