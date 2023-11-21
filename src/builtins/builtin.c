#include "minishell.h"
#include "libft.h"

bool	fire_builtin(t_shell *shell, char **argv)
{
	int	i;
	int	argc;
	int	status;

	i = 0;
	status = 0;
	argc = 0;
	if (!does_builtin_exist(shell, *argv))
		return (false);
	while (i < shell->builtins_size
		&& ft_strcmp(shell->builtins[i].command, *argv))
		i++;
	while (argv[argc])
		argc++;
	status = shell->builtins[i].__builtin_handler(shell, argc, argv);
	return (status == 0);
}

bool	does_builtin_exist(t_shell *shell, char *command)
{
	int	i;

	i = 0;
	while (i < shell->builtins_size)
	{
		if (ft_strcmp(shell->builtins[i].command, command) == 0)
			return (true);
		i++;
	}
	return (false);
}

