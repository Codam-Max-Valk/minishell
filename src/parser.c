#include "../include/libft.h"
#include "../include/minishell.h"
#include "../include/tokens.h"

static void print_tokens(t_token **tokens)
{
	t_token	*token;

	if (!tokens || !*tokens)
		return ;
	token = *tokens;
	while (token)
	{
		printf("Tag: %-16s : Content: %s\n",
			get_tag_name(token->tag), token->content);
		token = token->next;
	}
}

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

static t_token	*emplace_tokens(t_shell *shell, t_info **info, t_token *token)
{
	t_info	*node;
	t_info	*tmp_nod;
	t_token	*tmp_tok;
	size_t	index;
	char	*expander;

	index = 0;
	node = ft_calloc(1, sizeof(t_info));
	node->command = ft_calloc(16, sizeof(char *)); //Fix by calculating how many commands there are between the pipes. or Begin till (pipe / end)
	while (token && token->tag != T_PIPE && token->tag != T_END)
	{
		// if (token->tag == T_COMMAND
		// 	&& token->next->tag == T_EQUALS
		// 	&& (token->next->next->tag == T_COMMAND
		// 		|| token->next->next->tag == T_EXPANSION
		// 		|| token->next->next->tag == T_DOUBLE_QUOTE
		// 		|| token->next->next->tag == T_SINGLE_QUOTE))
		// {
		// 	printf("Yet to be implemented!\n");
		// 	//if (!token->next->next || !token->next->next->content)
		// 	//	expander = ft_strdup("\0");
		// 	//if (!expander)
		// 	//	return (NULL); //Too much freaking allocation goddammit.
		// 	//tmp_tok = token->next->next;
		// 	//if (!add_expansion(shell->environment, token->content, expander))
		// 	//	return (NULL);
		// 	token = token->next;
		// }
		if (token->tag == T_EXPANSION)
		{
			expander = find_expansion(shell->environment, token->content);
			if (!expander)
				expander = ft_strdup("\0");
			if (!expander)
				return (NULL);
			node->command[index] = ft_strdup(expander);
			if (!node->command[index])
				return (NULL);
			index++;
		}
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

static t_info	*parse_tokens(t_shell *shell, t_token **tokens)
{
	t_info		*info;
	t_token		*token;

	info = NULL;
	token = *tokens;
	if ((*tokens)->tag == T_END)
		return (NULL);
	while (token)
	{
		token = emplace_tokens(shell, &info, token);
		if (token->tag == T_PIPE || token->tag == T_END)
			token = token->next;
	}
	return (print_tokens(tokens), info);
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
		return (ft_printf("List is empty!\n"), NULL); //Free input
	info = parse_tokens(shell, &tokens);
	if (!info)
		return (NULL); //Tokenizer freees the tokens themself and returns null.
	token_lstclear(&tokens, token_free);
	return (info);
}
