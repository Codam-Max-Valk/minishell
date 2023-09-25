#include "../include/minishell.h"
#include "../include/libft.h"

char	*find_expansion(t_env **env, const char *key)
{
	t_env	*node;

	node = *env;
	while (node != NULL && strcmp(node->key, key) != 0)
		node = node->next;
	if (!node)
		return (NULL);
	return (node->value);
}

bool	add_expansion(t_env **env, char *key, char *value)
{
	int		i;
	t_env	*node;

	i = 0;
	node = *env;
	if (!value)
		add_environment_variable(env, key, "\0", 1);
	if (*value == '$')
		add_environment_variable(env, key, find_expansion(env, &value[1]), 1);
	else
		add_environment_variable(env, key, value, 1);
	return (true);
}
