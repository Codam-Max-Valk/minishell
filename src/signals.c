#include "../include/minishell.h"

extern int g_sig;

void	handle_control_c(int code)
{
	g_sig = 1;
	ft_putchar('\n');
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_control_d(t_shell *shell)
{
	ft_exit(shell, 0, NULL);
}

void	child_sig_handle(int code)
{
	if (code == SIGINT)
	{
		g_sig = 1;
		ft_putstr("\n");
		signal(SIGINT, child_sig_handle);
	}
}

void	register_signals(void)
{
	g_sig = 0;
	signal(SIGINT, handle_control_c);
	signal(SIGQUIT, SIG_IGN);
}