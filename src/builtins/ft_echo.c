#include "../../include/minishell.h"

static bool	is_option_n(char *arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	ft_echo(t_shell *shell, int ac, char **av)
{
	bool	option_n;
	int		i;

	i = 1;
	option_n = false;
	while (av[i] && ft_strncmp(av[i], "-n", 2) == 0)
	{
		if (is_option_n(av[i]) == true)
			option_n = true;
		i++;
	}
	while (av[i])
	{
		printf("%s", av[i]);
		if (i < (ac - 1))
			printf(" ");
		i++;
	}
	if (option_n == true)
		return (0);
	else
		return (printf("\n"));
}
