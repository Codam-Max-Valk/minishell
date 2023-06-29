#include "../include/minishell.h"
#include "../include/libft.h"

static t_env	*create_new_env_node(char *key, char *value)
{
	t_env	*env;

	if (ft_isnull(key) && ft_isnull(value))
		return (NULL);
	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	if (ft_isnull(env->key))
		return (free(env), NULL);
	env->value = ft_strdup(value);
	if (ft_isnull(env->value))
		return (free(env->key), free(env), NULL);
	return (env);
}

int	add_environment_variable(t_env **env, char *key, char *value)
{
	t_env	*node;
	t_env	*nnode;

	nnode = create_new_env_node(key, value);
	if (!nnode)
		return (0);
	if (!*env)
	{
		*env = nnode;
		return (1);
	}
	node = *env;
	while (node->next)
		node = node->next;
	node->next = nnode;
	return (1);
}

int	get_environment_size(t_env **env)
{
	size_t	i;
	t_env	*node;

	i = 0;
	if (!env || !*env)
		return (0);
	node = *env;
	while (node)
	{
		node = node->next;
		i++;
	}
	return (i);
}

t_env	*find_environment_key(t_env **env, char *key)
{
	t_env	*node;

	if (!env || !*env)
		return (NULL);
	node = *env;
	while (node)
	{
		if (strcmp(node->key, key) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

char	**find_environment_key_as_2d(t_env **env, char *key)
{
	const t_env	*node = find_environment_key(env, key);
	char		*s;
	char		*s2;

	if (!node)
		return (NULL);
	s = ft_strjoin(node->key, "=");
	if (!s)
		return (NULL);
	s2 = ft_strjoin_free(s, node->value);
	if (!s2)
		return (free(s), NULL);
	return ((char *[2]){s2, NULL});
}
