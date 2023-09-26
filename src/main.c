#include "../include/minishell.h"
#include "../include/libft.h"

t_env	*initialize_environment(char **envp)
{
	size_t		i;
	t_env		*env;
	char		**line;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		line = ft_split_first_occurrence(envp[i], '=');
		if (!line)
		{
			i++;
			continue ;
		}
		set_pair(&env, line[0], line[1]);
		free_double_array(line);
		i++;
	}
	return (env);
}

void	register_builtins(t_shell *shell)
{
	set_builtin(shell, "cd", ft_cd);
	set_builtin(shell, "pwd", ft_pwd);
	set_builtin(shell, "exit", ft_exit);
	set_builtin(shell, "echo", ft_echo);
	set_builtin(shell, "env", ft_env);
	set_builtin(shell, "export", ft_export);
	set_builtin(shell, "unset", ft_unset);
	set_builtin(shell, "debug", ft_debug);
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
	env = initialize_environment(envp);
	shell->environment = env;

	open_historyfile();
	register_builtins(shell);

	ft_printf("[Environment] %s\n", find_pair(&env, "PATH"));
	while (shell->exited)
	{
		register_signals();
		info = ms_readline(shell);
		if (!info)
		{
			continue ;
		}
		exec_loop(shell, info, envp);
	}
	return (EXIT_SUCCESS);
}
