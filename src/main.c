#include "../include/minishell.h"
#include "../include/libft.h"

char	*ft_readline(const char *s)
{
	static char	*line;

	line = NULL;
	if (line)
		free(line);
	line = readline(s);
	if (line && *line)
		add_history(line);
	return (line);
}

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
	t_env	*env;

	(void) argc;
	(void) argv;
	env = initialize_environment(envp);
	ft_printf("%s\n", *find_environment_key_as_2d(&env, "PATH"));
	while (true)
	{
		shell.last_read_line = ft_readline(">>");
	}
	return (EXIT_SUCCESS);
}
