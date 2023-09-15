#include "../../include/minishell.h"
#include "../../include/libft.h"

static void	register_builtin(t_shell *shell, t_builtin *in)
{
	const int	actual_size = get_builtin_size(shell);

	if (actual_size > 10)
	{
		ft_printf(
			"error: attempted to register builtint \'%s\' but limit was exceeded",
			in->command);
		free_builtin(in);
		return ;
	}
	if (shell->size != actual_size)
		shell->size = actual_size;
	shell->builtins[shell->size] = in;
	shell->size++;
}

bool	fire_builtin(t_shell *shell, char **argv)
{
	int	i;
	int	status;

	i = 0;
	if (!does_builtin_exist(shell, *argv))
		return (false);
	while (shell->builtins[i])
	{
		if (ft_strcmp(shell->builtins[i]->command, *argv) == 0)
		{
			status = shell->builtins[i]->__builtin_handler(10, &argv[1]);
			return (status == 0);
		}
		i++;
	}
	return (false);
}

bool	set_builtin(t_shell *shell, char *command, t_builtin_func func)
{
	t_builtin	*builtin;
	int			actual_size;
	
	if (!command || !*command)
		return (false);
	builtin = malloc(sizeof(t_builtin));
	if (!builtin)
		return (false);
	actual_size = get_builtin_size(shell);
	builtin->command = ft_strdup(command);
	builtin->__builtin_handler = func;
	if (!builtin->command)
		return (free(builtin), false);
	register_builtin(shell, builtin);
	return (true);
}

void	print_builtins(t_shell *shell)
{
	int	i;
	
	i = 0;
	while (shell->builtins[i])
	{
		ft_printf("[Builtin] (%d/%d) command: %s\n",
			i,
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