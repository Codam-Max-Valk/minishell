#include "../include/minishell.h"
#include "../include/libft.h"

int	read_input(char *name)
{
	char *str;

	while (*name != '=')
		name++;
	name++;
	name = ft_strjoin(name, " >> ");
	while (1)
	{
		str = readline(name);
		if (!str)
			return (EXIT_FAILURE); //Tijdelijk.
		free(str);
	}
}

int	main(int argc, char **argv, char **envp)
{
	while (ft_strncmp(*envp, "LOGNAME", 7))
		envp++;
	return (read_input(*envp));
}
