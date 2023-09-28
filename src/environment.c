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
		while (node && ft_strcmp(node->key, key))
			node = node->next;
		if (node)
			return (node);
	}
	if (shell->environment != NULL)
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

void	set_pairv2(t_shell *shell, char *key, char *value, t_envtype type)
{
	t_env	*node;
	char	*tmp;

	tmp = NULL;
	if (!shell)
		return ;
	node = find_pair(shell, &value[1]);
	if (!node)
		tmp = value;
	else
		tmp = node->value;

	if (type == ENVIRONMENT)
		node = env_addpair(&shell->environment, key, tmp);
	else if (type == LOCAL_ENVIRONMENT)
		node = env_addpair(&shell->expansion, key, tmp);

	if (!node)
	{
		perror("environment");
		exit(127);
	}

	//Addpair() can handle this crap if allocation doesn't go through
	if (type == ENVIRONMENT)
		env_lstaddback(&shell->environment, node);
	else if (type == LOCAL_ENVIRONMENT)
		env_lstaddback(&shell->expansion, node);
}

//Rewrite these functions under me.
void	sed_pair(t_shell *shell, char *key, char *value)
{
	t_env	*node;
	t_env	*content;

	if (ft_isnull(key))
		return ;
	node = find_pair(shell, key);
	if (!node)
	{
		//if (!add_pair(&shell->expansion, key, value))
		//	perror("cannot add variable to environment/expansion list");
		//return ;
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
