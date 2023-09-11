#include "../include/libft.h"
#include "../include/minishell.h"
#include "../include/tokens.h"

static char	*ft_readline(const char *s)
{
	static char	*line;

	line = NULL;
	if (line)
		free(line);
	line = readline(s);
	if (line && *line)
		add_history(line);
	return (line);
}

static t_list	*parse_tokens(t_token **tokens)
{
	t_readline *readline;

	readline = ft_calloc(1, sizeof(t_readline));
	if (!readline)
		return (NULL);
	readline->command = ft_calloc(2, sizeof(char *));
	readline->command[0] = ft_strdup((*tokens)->content);
	return (
		ft_printf("Warning: Parsing %d tokens in total\n",
			token_lstsize(*tokens)), ft_lstnew(readline));
}

t_list	*ms_readline(t_shell *shell, char *str)
{
	t_list	*list;
	t_token	*tokens;

	list = NULL;
	if (!str || !*str)
		return (NULL);
	
	shell->last_command = ft_readline(str);
	if (!shell->last_command)
		return (ft_printf("^D\n"), NULL); //For signals eventually.

	tokens = tokenizer2(shell->last_command);
	if (!tokens)
		return (NULL); //Free input
		
	list = parse_tokens(&tokens);
	if (!list)
		return (NULL); //Tokenizer freees the tokens themself and returns null.
	token_lstclear(&tokens, token_free);
	return (free(shell->last_command), list);
}

/*

	shell.last_read_line = ft_readline(">>");
		t_token *tokens = tokenizer2(shell.last_read_line);
		if (!tokens)
		{
			printf("List is empty\n");
			continue ;
		}
		else
		{
			while (tokens)
			{
				ft_printf("TAG: %s\t\t=>\tCONTENT: %s\n", get_tag_name(tokens->tag), tokens->content);
				tokens = tokens->next;
			}
		}

*/