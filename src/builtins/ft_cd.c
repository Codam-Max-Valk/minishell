#include "../../include/libft.h"
#include "../../include/minishell.h"

int	ft_cd(t_shell *shell, int argc, char **argv)
{
	char	*target;

	if (argv[1] == NULL)
		target = find_environment_key(shell->environment, "HOME")->value;
	else
		target = argv[1];
	if (chdir(target))
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
