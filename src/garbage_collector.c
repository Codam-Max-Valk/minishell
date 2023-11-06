#include "minishell.h"

void	cleanup_base(t_shell *shell)
{
	int i = 0;

	while (shell->builtins[i] != NULL)
	{
		free(shell->builtins[i]->command);
		free(shell->builtins[i]);
		i++;
	}
	free(shell);
}

static void	free_info(t_info *info)
{
	t_token *tmp;
	t_token *pos;
	int	i = 0;

	while (info->command[i])
	{
		free(info->command[i]);
		i++;
	}
	pos = info->inf;
	while (pos)
	{
		tmp = pos->next;
		free(pos->content);
		free(pos);
		pos = tmp;
	}
	pos = info->outf;
	while (pos)
	{
		tmp = pos->next;
		free(pos->content);
		free(pos);
		pos = tmp;
	}
}

void	clean_info(t_info **info)
{
	t_info	*tmp;
	t_info	*pos;

	pos = *info;
	while (pos)
	{
		tmp = pos->next;
		free_info(pos);
		free(pos);
		pos = tmp;
	}
	*info = NULL;
}
