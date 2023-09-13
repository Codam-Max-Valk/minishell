#include "../include/libft.h"
#include "../include/minishell.h"
#include "../include/tokens.h"

static void print_tokens(t_token **tokens)
{
//	t_token	*token;
//	if (!tokens || !*tokens)
//	{
//		printf("List is empty\n");
//		return ;
//	}
//	else
//	{
//		token = *tokens;
//		while (token)
//		{
//			ft_printf("TAG: %s\t\t=>\tCONTENT: %s\n", get_tag_name(token->tag), token->content);
//			token = token->next;
//		}
//	}
}

static char	*ft_readline(const char *s)
{
	static char	*line;
	char		*prefix;

	line = NULL;
	if (line)
		free(line);
	prefix = ft_strjoin(BOLD_GREEN, s);  // Malloc protection?
	prefix = ft_strjoin(prefix, RESET); // Malloc protection?
	line = readline(prefix);
	if (line && *line)
		add_history(line);
	return (line);
}

static t_info	*parse_tokens(t_token **tokens)
{
	t_info		*info;
	t_token		*token;
	t_file_node *node;
	size_t		index;

	info = ft_calloc(1, sizeof(t_info));
	if (!info)
		return (NULL);	
	node = NULL;
	index = 0;
	token = *tokens;
	
	//BEGIN of "Fix this later."
	info->command = ft_calloc(16, sizeof(char *));
	//END of "Fix this later."

	while (token->tag != T_PIPE && token->tag != T_END)
	{
		if (token->tag == T_COMMAND)
			info->command[index++] = ft_strdup(token->content);
	}
	ft_printf("Tokens parsed\n");
	return (print_tokens(tokens), info);
}

t_info	*ms_readline(t_shell *shell, char *str)
{
	t_info	*info;
	t_token	*tokens;

	info = NULL;
	tokens = NULL;
	if (!str || !*str)
		return (NULL);

	shell->last_command = ft_readline(str);
	if (!shell->last_command)
		return (ft_printf("^D\n"), NULL); //For signals eventually.

	tokens = tokenizer2(shell->last_command);
	if (!tokens)
		return (NULL); //Free input

	info = parse_tokens(&tokens);
	if (!info)
		return (NULL); //Tokenizer freees the tokens themself and returns null.
	token_lstclear(&tokens, token_free);
	return (free(shell->last_command), info);
}

/*

	shell.last_read_line = ft_readline(">>");
		t_token *tokens = tokenizer2(shell.last_read_line);
		

*/