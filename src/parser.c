#include "../include/libft.h"
#include "../include/minishell.h"
#include "../include/tokens.h"

static void print_tokens(t_token **tokens)
{
	//t_token	*token;
	//if (!tokens || !*tokens)
	//{
	//	printf("List is empty\n");
	//	return ;
	//}
	//else
	//{
	//	token = *tokens;
	//	while (token)
	//	{
	//		ft_printf("TAG: %s\t\t=>\tCONTENT: %s\n", get_tag_name(token->tag), token->content);
	//		token = token->next;
	//	}
	//}
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

static t_token	*emplace_tokens(t_info **info, t_token **tokens)
{
	t_info	*node;
	t_info	*tmp_nod;
	t_token	*token;
	t_token	*tmp_tok;
	size_t	index;

	index = 0;
	token = *tokens;
	node = ft_calloc(1, sizeof(t_info));
	node->command = ft_calloc(16, sizeof(char *)); //Fix by calculating how many commands there are between the pipes. or Begin till (pipe / end)
	while (token && token->tag != T_PIPE && token->tag != T_END)
	{
		if (token->tag == T_COMMAND && token->next->tag == T_EQUALS)
		{
			if (token->next->next->tag != T_COMMAND)
			{
				token = token->next;
				ft_printf("Not a valid key & value argument\n");
				continue ;
			}
			ft_printf("[Key] = %s\n[Value] = %s\n",
				token->content,
				token->next->next->content);
			token = token->next->next;
		}
		else if (token->tag == T_EXPANSION); //Lmaooo!
		else if (token->tag == T_COMMAND || token->tag == T_DOUBLE_QUOTE || token->tag == T_SINGLE_QUOTE)
			node->command[index++] = ft_strdup(token->content);
		else if (token->tag == T_REDIRECT_OUT || token->tag == T_APPEND)
		{
			tmp_tok = token_dup(token);
			if (!tmp_tok)
				return (ft_printf("error: cannot duplicate token\n"), NULL); //Add error handling.
			token_addback(&node->outf, tmp_tok);
			tmp_tok = NULL;
		}
		else if (token->tag == T_REDIRECT_IN || token->tag == T_HERE_DOC)
		{
			tmp_tok = token_dup(token);
			if (!tmp_tok)
				return (ft_printf("error: cannot duplicate token\n"), NULL); //Add error handling.
			token_addback(&node->inf, tmp_tok);
			tmp_tok = NULL;
		}
		token = token->next;
	}
	if (!*info)
		*info = node;
	else
	{
		tmp_nod = *info;
		while (tmp_nod->next)
			tmp_nod = tmp_nod->next;
		tmp_nod->next = node;
	}
	return (token);
}

static t_info	*parse_tokens(t_token **tokens)
{
	t_info		*info;
	t_token		*token;

	info = NULL;
	token = *tokens;
	if ((*tokens)->tag == T_END)
		return (NULL);
	while (token)
	{
		token = emplace_tokens(&info, &token);
		if (token->tag == T_PIPE || token->tag == T_END)
			token = token->next;
	}
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
		return (ft_printf("List is empty!\n"), NULL); //Free input

	info = parse_tokens(&tokens);
	if (!info)
		return (NULL); //Tokenizer freees the tokens themself and returns null.
	token_lstclear(&tokens, token_free);
	return (free(shell->last_command), info);
}
