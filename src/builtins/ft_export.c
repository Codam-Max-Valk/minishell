#include "../../include/libft.h"
#include "../../include/minishell.h"

bool	verify_export(t_shell *shell, char *key, char *value)
{
	if (find_pair(shell, key) && value)
		env_lstrepl_value(&shell->environment, key, value);
	else if (find_pair(shell, key) && value == NULL)
		return (true);
	else
	env_lstaddback(&shell->environment, env_addpair(key, value, ENVIRONMENT));
}

int	print_list(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

char	*set_value(char *s)
{
	int	i;

	i = 0;
	if (!ft_strchr(s, '='))
		return (NULL);
	while (s[i] != '=')
		i++;
	if (s[i] == '=')
		i++;
	return (ft_safe_strdup(&s[i]));
}

char	*set_key(char *s)
{
	int	i;

	i = 0;
	if (s[0] && !(ft_isalpha(s[0]) || s[0] == '_'))
		return (printf("error1\n"), NULL);
	while (s[i])
	{
		if (s[i] == '=')
			return (ft_substr(s, 0, i));
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (printf("error2\n"), NULL);
		i++;
	}
	return (ft_strdup(s));
}

int	ft_export(t_shell *shell, int argc, char **argv)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	if (argc == 1)
		return (print_list(shell->environment));
	while (argv[i])
	{
		value = NULL;
		key = set_key(argv[i]);
		if (!key)
			printf("error3\n");
		else
		{
			value = set_value(argv[i]);
			verify_export(shell, key, value);
		}
		if (key)
			free(key);
		if (value)
			free(value);
		i++;
	}
	return (EXIT_SUCCESS);
}
