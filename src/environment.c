#include "../include/minishell.h"
#include "../include/libft.h"

t_env	*find_pair(t_shell *shell, char *key)
{
	t_env	*node;

	if (ft_isnull(key))
		return (NULL);
	if (shell->expansion)
	{
		node = shell->expansion;
		while (node && ft_strcmp(node->key, key))
			node = node->next;
		if (node)
			return (node);
	}
	if (shell->environment)
	{
		node = shell->environment;
		while (node && ft_strcmp(node->key, key))
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


//Rewrite these functions under me.
void	set_pair(t_env **env, char *key, char *value)
{
	t_env	*node;

	if (ft_isnull(key))
		return ;
	if (!env || !*env)
	{
		add_pair(env, key, value);
		return ;
	}
	node = *env;
	while (node != NULL && ft_strcmp(node->key, key) == 0)
		node = node->next;
	if (!node)
	{
		add_pair(env, key, value);
		return ;
	}
	env_lstdelone(env, key);
	if (!add_pair(env, key, value))
		perror("cannot add variable to environment/expansion list");
}

void	sed_pair(t_shell *shell, char *key, char *value)
{
	t_env	*node;
	t_env	*content;

	if (ft_isnull(key))
		return ;
	node = find_pair(shell, key);
	if (!node)
	{
		if (!add_pair(&shell->expansion, key, value))
			perror("cannot add variable to environment/expansion list");
		return ;
	}
	free(node->value);
	if (ft_isnull(value) || *value != '$')
		node->value = ft_safe_strdup(value);
	else
		content = find_pair(shell, key);
	if (*value == '$' && content)
		node->value = ft_safe_strdup(content->value);
	else
		node->value = ft_safe_strdup(NULL);
	if (!node->value)
		perror("cannot add variable to environment/expansion list");
}

bool	add_pair(t_env **lst, char *key, char *value)
{
	t_env	*node;
	t_env	*content;

	node = malloc(sizeof(t_env));
	if (!node)
		return (false);
	node->key = ft_strdup(key);
	if (!node->key)
		return (free(node), false);

	if (ft_isnull(value) || *value != '$')
		node->value = ft_safe_strdup(value);
	else if (*value == '$')
		node->value = ft_safe_strdup("Uh");
	node->next = NULL;
	env_lstaddback(lst, node);
	return (true);
}
