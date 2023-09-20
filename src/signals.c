#include "../include/minishell.h"


static void	handle_control_c(int code)
{
	ft_putchar('\n');
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_control_d(t_shell *shell)
{
	//fire_builtin(shell, &"exit");
}

void	register_signals(void)
{
	signal(SIGINT, handle_control_c);
	signal(SIGQUIT, SIG_IGN);
}