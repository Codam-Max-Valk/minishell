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
	set_builtin(shell, "cd", ft_cd);
	set_builtin(shell, "pwd", ft_pwd);
	set_builtin(shell, "exit", ft_exit);
	set_builtin(shell, "echo", ft_echo);
	set_builtin(shell, "env", ft_env);
	set_builtin(shell, "export", ft_export);
	set_builtin(shell, "unset", ft_unset);
	set_builtin(shell, "debug", ft_debug);
	set_builtin(shell, "calc", ft_calc);

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
	//environment_init(shell, envp);

	ft_printf("[Environment] %s\n", find_pair_content(shell, "PATH"));
	while (shell->exited)
	{
		register_signals();
		info = ms_readline(shell);
		if (!info)
		{
			continue ;
		}
		exec_loop(shell, &info, envp);
		clean_info(&info);
	}
	cleanup_base(shell);
	return (EXIT_SUCCESS);
}
