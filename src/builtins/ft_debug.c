#include "../../include/minishell.h"
#include "../../include/libft.h"

int	ft_debug(t_shell *shell, int ac, char **av)
{
	t_env	*env;

	if (ft_strcmp(av[1], "env") == 0)
	{
		if (!shell->environment)
			return (printf("error: environment list is still empty!\n"), EXIT_FAILURE);
		env = shell->environment;
	}
	else if (ft_strcmp(av[1], "exp") == 0)
	{
		if (!shell->expansion)
			return (printf("error: expansions list is still empty!\n"), EXIT_FAILURE);
		env = shell->expansion;
	}
	else
		return (printf("error: usage: debug <env/exp>\n"), EXIT_FAILURE);
	
	while (env)
	{
		printf("[%sDebug%s] Key: %-4s :\tValue: %s\n", BOLD_RED, RESET, env->key, env->value);
		env = env->next;
	}	
	return (EXIT_SUCCESS);
}
