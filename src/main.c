#include "../include/minishell.h"
#include "../include/libft.h"

t_env	*initialize_environment(char **envp)
{
	size_t		i;
	t_env		*env;
	char		**line;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		line = ft_split_first_occurrence(envp[i], '=');
		if (!line)
		{
			i++;
			continue ;
		}
		add_environment_variable(&env, line[0], line[1]);
		free_double_array(line);
		i++;
	}
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_list	*tokens;
	t_env	*env;

	(void) argc;
	(void) argv;
	env = initialize_environment(envp);
	ft_printf("%s\n", *find_environment_key_as_2d(&env, "PATH"));
	while (true)
	{
		tokens = ms_readline(&shell, ">>");
		if (!tokens)
			continue ;
		if (strcmp(((t_readline *)tokens->content)->command[0], "exit") == 0)
			break ;
	}
	return (EXIT_SUCCESS);
}
