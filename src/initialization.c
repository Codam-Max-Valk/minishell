#include "../include/minishell.h"

static t_env *add(char *key, char *value)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	env->key = key;
	env->value = value;
	env->next = NULL;
	return (env);
}

static void	push(t_env **env, char *key, char *value)
{
	t_env *vars;

	if (!env && !*env)
	{
		env = add(key, value);
		return ;
	}

	vars = *env;
	while (vars->next)
		vars = vars->next;
	vars->next = ft_calloc(1, sizeof(t_env));
	vars->next->key = ft_strdup(key);
	vars->next->value = ft_strdup(value);
}

static int	get_dictionary_size(t_env **env)
{
	int		i;
	t_env	*key;

	//if (!env && !*env)
	//	return (0);
	i = 0;
	key = *env;
	while (env[i])
	{
		key = key->next;
		i++;
	}
	return (i);
}

static void	free_keys(char **keys)
{
	free(keys[0]);
	free(keys[1]);
}

t_env	*setup_environment(char **envp)
{
	t_env	*env;
	int		i;
	char	**index;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		index = ft_split(envp[i], '=');
		if (!index)
			return (free_keys(index), env);
		push(&env, index[0], index[1]);
		//printf("%s -> %s", env->key, env->value);
		free_keys(index);
		i++;
	}
	ft_printf("Added %d keys to the environment!\n", get_dictionary_size(&env));
	return (env);
}
