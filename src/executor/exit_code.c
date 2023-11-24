#include "../../include/minishell.h"

void	update_exit(t_shell *shell)
{
	shell->exit_code[1] = shell->exit_code[0];
	shell->exit_code[0] = 0;
}

void	print_mini_err(t_shell *shell, char *func, int code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(func, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(code), STDERR_FILENO);
}
