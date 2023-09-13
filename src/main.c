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

void	lk()
{
	system("leaks -q Minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_info	*info;
	t_env	*env;

	atexit(&lk);
	(void) argc;
	(void) argv;
	env = initialize_environment(envp);
	ft_printf("%s\n", *find_environment_key_as_2d(&env, "PATH"));
	while (true)
	{
		info = ms_readline(&shell, ">>");
		if (!info)
			continue ;
		exec_loop(info, envp);
	}
	return (EXIT_SUCCESS);
}
