
#include "../../include/minishell.h"
#include "../../include/libft.h"

int	ft_exit(t_shell *shell, int argc, char **argv)
{
	printf("exit\n");
	return (shell->exited = 0);
}
