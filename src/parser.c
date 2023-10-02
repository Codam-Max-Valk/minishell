#include "../include/libft.h"
#include "../include/minishell.h"
#include "../include/tokens.h"

static void	print_tokens(t_token **tokens)
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

static t_token	*emplace_tokens(t_shell *shell, t_info **info, t_token *token)
{
	t_info	*node;
	t_info	*tmp_nod;
	t_token	*tmp_tok;
	size_t	index;
	char	*expander;
	char	**key_value;
	char	*value;

	index = 0;
	node = ft_calloc(1, sizeof(t_info));
	value = NULL;
	if (!node)
		return (NULL);
	node->command = ft_calloc(16, sizeof(char *)); //Fix by calculating how many commands there are between the pipes. or Begin till (pipe / end)
	while (token && token->tag != T_PIPE && token->tag != T_END)
	{
		if (token->tag == T_EQUALS)
		{
			key_value = ft_split(token->content, EQUALS);
			if (!key_value)
				return (NULL);
			if (key_value[1])
			{
				value = ft_strtrim(key_value[1], TOKEN_DELIMITOR);
				if (!value)
				{
					value = NULL;
					return (free_double_array(key_value), NULL);
				}
			}
			sed_pair(shell, key_value[0], value, LOCAL_ENVIRONMENT);
			free_double_array(key_value);
			value = NULL;
		}
		else if (token->tag == T_EXPANSION)
		{
			expander = find_pair_content(shell, token->content);
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
		{
			node->command[index++] = ft_strdup(token->content);
		}
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

t_info	*parse_tokens(t_shell *shell, t_token **tokens)
{
	t_info		*info;
	t_token		*token;

	info = NULL;
	token = *tokens;
	if ((*tokens)->tag == T_END)
		return (NULL);
	print_tokens(tokens);
	while (token)
	{
		token = emplace_tokens(shell, &info, token);
		if (token->tag == T_PIPE || token->tag == T_END)
			token = token->next;
	}
	return (info);
}

