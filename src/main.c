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
	rl_on_new_line();
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_list	*env;

	(void) argc;
	(void) argv;
	env = setup_environment(envp);
	printf("Welcome back %s, to your personal terminal!\n",
		&(find_environment_key(&env, "LOGNAME")->value)[1]);
	while (true)
	{
		shell.last_read_line = ft_readline(">>");
	}
	return (EXIT_SUCCESS);
}
