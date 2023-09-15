#include "../../include/minishell.h"
#include "../../include/libft.h"

int	get_builtin_size(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->builtins[0])
		return (0);
	while (shell->builtins[i])
		i++;
	return (i);
}

bool	does_builtin_exist(t_shell *shell, char *command)
{
	int	i;

	i = 0;
	while (shell->builtins[i])
	{
		if (ft_strcmp(shell->builtins[i]->command, command) == 0)
			return (true);
		i++;
	}
	return (false);
};
