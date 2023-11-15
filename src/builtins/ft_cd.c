#include "../../include/libft.h"
#include "../../include/minishell.h"

char	*find_home_path(t_shell *shell, char *av)
{
	int		i;
	char	*new_path;

	i = 0;
	if (av[1] != '\0' && ft_strchr(av, '~'))
		new_path = ft_strjoin(find_pair_content(shell, "HOME"), &av[1]);
	else if (av[0] == '~' && av[1] == '\0')
		new_path = ft_safe_strdup(find_pair_content(shell, "HOME"));
	else
		new_path = ft_strdup(av);
	return (new_path);
}

int	ft_cd(t_shell *shell, int argc, char **argv)
{
	char	*target;
	char	*oldpwd;

	if (argc > 2)
		return (ft_putstr_fd("cd", 2), ft_putendl_fd(": too many arguments", 2), EXIT_FAILURE);
	if (ft_strcmp("-", argv[1]) == 0)
		target = ft_safe_strdup(find_pair_content(shell, "OLDPWD"));
	else if (argv[1] == NULL)
		target = ft_safe_strdup(find_pair_content(shell, "HOME"));
	else
		target = find_home_path(shell, argv[1]);
	if (target == NULL)
		return (perror("malloc"), EXIT_FAILURE);
	oldpwd = getcwd(NULL, 0);
	if (oldpwd)
	{
		env_lstrepl_value(&shell->environment, "OLDPWD", oldpwd);
		free(oldpwd);
	}
	if (chdir(target))
	{
		free(target);
		return (perror("cd"), EXIT_FAILURE);
	}
	if (target)
		free(target);
	return (EXIT_SUCCESS);
}
