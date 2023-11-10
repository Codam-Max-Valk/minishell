#include "../include/minishell.h"
#include "../include/libft.h"

t_env	*find_pair(t_shell *shell, char *key)
{
	t_env	*node;

	node = NULL;
	if (ft_isnull(key))
		return (NULL);
	if (shell->expansion != NULL)
	{
		node = shell->expansion;
		while (node && ft_strcmp(node->key, key) != 0)
			node = node->next;
		if (node)
			return (node);
	}
	if (shell->environment != NULL)
	{
		node = shell->environment;
		while (node && ft_strcmp(node->key, key) != 0)
			node = node->next;
		if (node)
			return (node);
	}
	return (NULL);
}

char	*find_pair_list(t_env **env, char *key)
{
	t_env	*node;

	if (ft_isnull(key) || !*env)
		return (NULL);
	node = *env;
	while (node && ft_strcmp(node->key, key))
		node = node->next;
	if (!node)
		return (NULL);
	return (node->value);
}

char	*find_pair_content(t_shell *shell, char *key)
{
	t_env	*node;

	if (ft_isnull(key))
		return (NULL);
	node = find_pair(shell, key);
	if (!node)
		return (NULL);
	return (node->value);
}

/// @brief	Sets a new pair in the defined environment type
///			if the key does not exist in the environment yet
/// @param shell Head struct of Minishell.
/// @param key Environment key
/// @param value Value to be. (Is nullable).
/// @param type Environment type
void	set_pairv2(t_shell *shell, char *key, char *value, t_envtype type)
{
	t_env	*node;
	char	*tmp;
	int		pos;

	pos = 0;
	if (!shell)
		return ;
	tmp = NULL;
	node = find_pair(shell, key);
	if (node)
		return ;
	if (ft_isnull(value))
		tmp = "\0";
	else if (value && *value != '$')
		tmp = value;
	else if (value && *value == '$')
	{
		node = find_pair(shell, &value[1]);
		if (node)
			tmp = node->value;
	}
	node = env_addpair(key, tmp, type);
	if (!node)
		return ;
	if (type == ENVIRONMENT)
		env_lstaddback(&shell->environment, node);
	else if (type == LOCAL_ENVIRONMENT)
		env_lstaddback(&shell->expansion, node);
}

void	sed_pair(t_shell *shell, char *key, char *value, t_envtype type)
{
	t_env	*node;
	t_env	*content;

	if (ft_isnull(key))
		return ;
	node = find_pair(shell, key);
	if (!node)
	{
		set_pairv2(shell, key, value, type);
		return ;
	}
	if (node->type == LOCAL_ENVIRONMENT)
		env_lstdelone(&shell->expansion, key);
	else if (node->type == ENVIRONMENT)
		env_lstdelone(&shell->environment, key);
	set_pairv2(shell, key, value, node->type);
}
