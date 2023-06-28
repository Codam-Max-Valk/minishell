#include "../include/minishell.h"

static t_env_key	*add(char *key, char *value)
{
	t_env_key	*env_key;

	env_key = ft_calloc(1, sizeof(t_env_key));
	if (!env_key)
		return (NULL);
	env_key->key = ft_strdup(key);
	env_key->value = ft_strdup(value);
	return (env_key);
}

static int	push(t_list **env, char **s)
{
	const t_env_key	*env_key = add(s[0], s[1]);

	if (!env_key)
		return (0);
	if (!ft_lstadd_back_content(env, (t_env_key *)env_key))
		return (free_envkey(env_key), 0);
	return (1);
}

t_env_key	*find_environment_key(t_list **env, char *key)
{
	t_list		*node;
	t_env_key	*envkey;

	node = *env;
	envkey = NULL;
	while (node)
	{
		envkey = (t_env_key *)node->content;
		if (ft_strncmp(envkey->key, key, ft_strlen(key)) == 0)
			return (envkey);
		node = node->next;
	}
	return (NULL);
}

t_list	*setup_environment(char **envp)
{
	t_list		*env;
	t_env_key	*key;
	char		**index;
	int			i;

	env = NULL;
	key = NULL;
	i = 0;
	while (envp[i])
	{
		index = ft_split(envp[i], '=');
		if (ft_isnull(index[1]))
		{
			i++;
			continue ;
		}
		push(&env, index);
		free_double_array(index);
		i++;
	}
	return (env);
}

void	free_envkey(t_env_key *ek)
{
	free(ek->key);
	free(ek->value);
	free(ek);
}

//Krijgt een opschoning nog.