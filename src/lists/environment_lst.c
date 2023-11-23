#include "../include/minishell.h"
#include "../include/libft.h"

t_env	*env_addpair(char *key, char *value, t_envtype type)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->value = NULL;
	node->key = ft_strdup(key);
	if (!node->key)
		return (free(node), NULL);
	if (value)
		node->value = ft_safe_strdup(value);
	if (value && !node->value)
		return (free(value), NULL);
	node->type = type;
	node->next = NULL;
	return (node);
}

void	env_lstrepl_value(t_env **lst, char *key, char *value)
{
	t_env	*node;

	node = *lst;
	while (node && ft_strcmp(node->key, key) != 0)
		node = node->next;
	if (!node)
		return ;
	if (node->value)
		free(node->value);
	node->value = NULL;
	if (value)
		node->value = ft_safe_strdup(value);
	if (!node->value)
		return (env_lstdelone(lst, key));
}

t_env	*env_lstback(t_env **env)
{
	t_env	*node;

	if (!env || !*env)
		return (NULL);
	node = *env;
	while (node->next)
		node = node->next;
	return (node);
}

void	env_lstaddback(t_env **env, t_env *new)
{
	t_env	*node;

	if (!env || !*env)
	{
		*env = new;
		return ;
	}
	node = env_lstback(env);
	node->next = new;
}

void	env_lstdelone(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
