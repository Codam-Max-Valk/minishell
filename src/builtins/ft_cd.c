#include "../../include/libft.h"
#include "../../include/minishell.h"

char	*find_home_path(t_shell *shell, char *av)
{
	int		i;
	char	*new_path;

	i = 0;
	if (av[1] != '\0' && ft_strchr(av, '~'))
		new_path = ft_strjoin(find_pair(&shell->environment, "HOME"), &av[1]);
	else if (av[0] == '~' && av[1] == '\0')
		new_path = find_pair(&shell->environment, "HOME");
	else
		new_path = av;
	return (new_path);
}

int	ft_cd(t_shell *shell, int argc, char **argv)
{
	char	*target;

	if (argc > 2)
		return (ft_putstr_fd("cd", 2), ft_putendl_fd(": too many arguments", 2), EXIT_FAILURE);
	if (argv[1] == NULL)
		target = find_pair_list(&shell->environment, "HOME");
	else
		target = find_home_path(shell, argv[1]);
	if (chdir(target))
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
