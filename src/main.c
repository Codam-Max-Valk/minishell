#include "../include/minishell.h"
#include "../include/libft.h"

void	environment_init(t_shell *shell, char **envp)
{
	size_t		i;
	char		**line;

	i = 0;
	while (envp[i])
	{
		line = ft_split_first_occurrence(envp[i], '=');
		if (!line)
		{
			i++;
			continue ;
		}
		set_pairv2(shell, line[0], line[1], ENVIRONMENT);
		free_double_array(line);
		i++;
	}
}

void	builtins_init(t_shell *shell)
{
	t_builtin	*map;

	map = ft_calloc(MAX_BUILTIN, sizeof(t_builtin));
	if (!map)
	{
		shell->builtins = NULL;
		return ;
	}
	map[shell->builtins_size++] = (t_builtin){"cd", ft_cd};
	map[shell->builtins_size++] = (t_builtin){"pwd", ft_pwd};
	map[shell->builtins_size++] = (t_builtin){"exit", ft_exit};
	map[shell->builtins_size++] = (t_builtin){"echo", ft_echo};
	map[shell->builtins_size++] = (t_builtin){"env", ft_env};
	map[shell->builtins_size++] = (t_builtin){"export", ft_export};
	map[shell->builtins_size++] = (t_builtin){"unset", ft_unset};
	map[shell->builtins_size++] = (t_builtin){"debug", ft_debug};
	map[shell->builtins_size++] = (t_builtin){"calc", ft_calc};
	shell->builtins = map;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	t_info	*info;
	t_env	*env;

	(void) argc;
	(void) argv;
	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (EXIT_FAILURE);
	shell->exited = 1;

	history_init();
	builtins_init(shell);
	environment_init(shell, envp);
	if (!shell->builtins)
		return (EXIT_FAILURE);
	shell->stdin_fd = dup(STDIN_FILENO);
	shell->stdout_fd = dup(STDOUT_FILENO);
	if (DEBUG)
	{
		ft_printf("[Environment] %s\n", find_pair_content(shell, "PATH"));
		ft_printf("[Debug] %d builtins registered\n", shell->builtins_size);
	}
	while (shell->exited)
	{
		register_signals();
		info = ms_readline(shell);
		if (!info)
			continue ;
		exec_loop(shell, &info, envp);
		clean_info(&info);
	}
	cleanup_base(shell);
	return (EXIT_SUCCESS);
}
