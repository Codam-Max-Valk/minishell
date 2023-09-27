#include "../include/libft.h"
#include "../include/minishell.h"
#include "../include/tokens.h"

static char	*ft_readline(void)
{
	static char	*line = NULL;
	char		*prefix;

	if (line)
		free(line);
	line = NULL;
	line = readline(PREFIX);
	if (line && *line)
		ms_add_history(line);
	return (line);
}

t_info	*ms_readline(t_shell *shell)
{
	t_info	*info;
	t_token	*tokens;

	info = NULL;
	tokens = NULL;
	shell->last_command = ft_readline();
	if (shell->last_command == NULL)
		return (handle_control_d(shell), NULL);
	tokens = tokenizer2(shell->last_command);
	if (!tokens)
		return (NULL);
	info = parse_tokens(shell, &tokens);
	if (!info)
		return (token_lstclear(&tokens, token_free), NULL);
	token_lstclear(&tokens, token_free);
	return (info);
}
