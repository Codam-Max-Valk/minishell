#include "../include/minishell.h"
#include "../include/libft.h"

void	handle_signals()
{
	rl_on_new_line();
}

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
	t_env	*env;

	(void) argc;
	(void) argv;
	env = setup_environment(envp);
	while (true)
	{
		shell.last_read_line = ft_readline(">>");
	}

	return (EXIT_SUCCESS);
}
