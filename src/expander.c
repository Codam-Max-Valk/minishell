#include "../include/minishell.h"
#include "../include/libft.h"

char *find_expansion(t_env **env, char *key)
{
	char	*value;
	t_env	*node;

	value = NULL;
	node = *env;
	while (!node)
	{
		node = node->next;
	}

	return (value);
}
