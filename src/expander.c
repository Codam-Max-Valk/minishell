#include "../include/minishell.h"
#include "../include/libft.h"

char *find_expansion(t_env **env, const char *key)
{
	t_env *node;

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
	if (!key || !*key)
		return (false);
	if (*key == '$')
		add_environment_variable(env, key, find_expansion(env, value));
	else
		add_environment_variable(env, key, value);
	return (true);
	/*
	if (token->next->next->tag != T_COMMAND)
			{
				token = token->next;
				ft_printf("Not a valid key & value argument\n");
				continue ;
			}
			ft_printf("[Key] = %s\n[Value] = %s\n",
				token->content,
				token->next->next->content);
			token = token->next->next;*/
}

int test_case()
{
	t_env *env = ft_calloc(1, sizeof(t_env));
	t_env *env1 = ft_calloc(1, sizeof(t_env));
	t_env *env2 = ft_calloc(1, sizeof(t_env));
	t_env *env3 = ft_calloc(1, sizeof(t_env));
	t_env *env4 = ft_calloc(1, sizeof(t_env));
	
	env->key = ft_strdup("env1");
	env1->key = ft_strdup("env2");
	env2->key = ft_strdup("env3");
	env3->key = ft_strdup("env4");
	env4->key = ft_strdup("env5");
	env->value = ft_strdup("Im environment 1");
	env1->value = ft_strdup("Hell nee");
	env2->value = ft_strdup("Hell yah");
	env3->value = ft_strdup("Hell yes");
	env4->value = ft_strdup("Hell nope");
	env->next = env1;
	env1->next = env2;
	env2->next = env3;
	env3->next = env4;
	env4->next = NULL;

	char *key = find_expansion(&env, "env3");
	ft_printf("Found?: %s\n",  key);
	return (1);
}
