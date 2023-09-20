#include "../../include/libft.h"
#include "../../include/minishell.h"

int	ft_pwd(t_shell *shell, int argc, char **argv)
{
	char	*cwd;

	(void)shell;
	(void)argc;
	(void)argv;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd");
		return (EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}
