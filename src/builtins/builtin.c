#include "../../include/minishell.h"
#include "../../include/libft.h"

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
	while (i < shell->builtins_size && ft_strcmp(shell->builtins[i].command, *argv))
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

void	print_builtins(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->builtins[i].command != NULL)
	{
		ft_printf("[Builtin] (%d/%d) command: %s\n",
			i + 1,
			MAX_BUILTIN,
			shell->builtins[i].command);
		i++;
	}
}

void	free_builtin(t_builtin *in)
{
	free(in);
}
