#include "../../include/minishell.h"
#include "../../include/libft.h"

int	ft_env(t_shell *shell, int argc, char **argv)
{
	t_env	*tmp;

	tmp = *shell->environment;
	while (tmp != NULL)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
