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
	free_double_array(info->command);
	token_lstclear(&info->inf, token_free);
	token_lstclear(&info->outf, token_free);
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

void	clean_tokens(t_token **tokens)
{
	t_token *tmp;
	t_token *pos;

	pos = *tokens;
	while (pos)
	{
		tmp = pos->next;
		free(pos->content);
		free(pos);
		pos = tmp;
	}
	*tokens = NULL;
}
