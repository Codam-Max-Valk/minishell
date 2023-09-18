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
	while (i < MAX_BUILTIN && ft_strcmp(shell->builtins[i]->command, *argv))
		i++;
	while (argv[argc])
		argc++;
	status = shell->builtins[i]->__builtin_handler(shell, argc, argv);
	return (status == 0);
}

bool	set_builtin(t_shell *shell, char *command, t_builtin_func func)
{
	const int	actual_size = get_builtin_size(shell);
	t_builtin	*builtin;

	if (!command || !*command)
		return (false);
	if (actual_size > MAX_BUILTIN)
	{
		return (ft_printf(
			"error: attempted to register builtin \'%s\' but limit was exceeded", command),
			false);
	}
	builtin = malloc(sizeof(t_builtin));
	if (!builtin)
		return (false);
	builtin->command = ft_strdup(command);
	builtin->__builtin_handler = func;
	if (!builtin->command)
		return (free(builtin), false);
	shell->builtins[shell->size] = builtin;
	shell->size++;
	return (true);
}

void	print_builtins(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->builtins[i])
	{
		ft_printf("[Builtin] (%d/%d) command: %s\n",
			i + 1,
			shell->size,
			shell->builtins[i]->command);
		i++;
	}
}

void	free_builtin(t_builtin *in)
{
	free(in->command);
	free(in);
}
