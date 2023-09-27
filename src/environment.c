#include "../include/minishell.h"
#include "../include/libft.h"

static t_env	*env_lstback(t_env **env)
{
	t_env *node;

	if (!env || !*env)
		return (NULL);
	node = *env;
	while (node->next)
		node = node->next;
	return (node);
}

static void	env_lstaddback(t_env **env, t_env *new)
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

static bool	add_pair(t_env **lst, char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (false);
	node->key = ft_strdup(key);
	if (!node->key)
		return (free(node), false);
	
	if (ft_isnull(value))
		node->value = ft_strdup("\0");
	else if (*value == '$')
		node->value = "FIND EXPANSION";
	else
		node->value = ft_strdup(value);
	if (!node->value)
		node->value = NULL;
	node->next = NULL;
	env_lstaddback(lst, node);
	return (true);
}

char	*find_pair(t_env **env, char *key)
{
	t_env	*node;

	if (!env || !*env)
		return (NULL);
	node = *env;
	while (node != NULL && ft_strcmp(node->key, key))
		node = node->next;
	if (!node)
		return (NULL);
	return (node->value);
}

void	del_pair(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
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
	del_pair(env, key);
	if (!add_pair(env, key, value))
	{
		perror("cannot add variable to environment/expansion list");
		return ;
	}
}
