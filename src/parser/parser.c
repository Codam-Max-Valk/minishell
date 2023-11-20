#include "../include/libft.h"
#include "../include/minishell.h"
#include "../include/tokens.h"

static bool	find_variable(t_info *node, t_shell *shell,
	t_token *token, int index)
{
	char	*expander;

	expander = find_pair_content(shell, token->content);
	if (!expander)
		expander = ft_strdup("\0");
	if (!expander)
		return (false);
	node->command[index] = ft_strdup(expander);
	if (!node->command[index])
		return (false);
	return (true);
}

static bool	add_variable(t_shell *shell, t_token *token)
{
	char	**key_value;
	char	*value;

	if (!shell || !token)
		return (false);
	key_value = ft_split_first_occurrence(token->content, EQUALS);
	value = NULL;
	if (!key_value)
		return (NULL);
	if (key_value[1])
	{
		value = ft_strtrim(key_value[1], TOKEN_DELIMITOR);
		if (!value)
			return (free_double_array(key_value), false);
	}
	sed_pair(shell, key_value[0], value, LOCAL_ENVIRONMENT);
	free_double_array(key_value);
	return (true);
}

static bool	add_redirect_token(t_info *node, t_token *token)
{
	t_token	*tmp;

	tmp = token_dup(token);
	if (!tmp)
		return (printf("error: cannot duplicate token\n"), false);
	if (token->tag == T_REDIRECT_IN || token->tag == T_HERE_DOC)
		token_addback(&node->inf, tmp);
	if (token->tag == T_REDIRECT_OUT || token->tag == T_APPEND)
		token_addback(&node->outf, tmp);
	return (true);
}

static int	add_tokens_back(t_shell *shell, t_info *node,
	t_token *token, int index)
{
	if (token->tag == T_EQUALS)
	{
		if (!add_variable(shell, token))
			return (-1);
		index++;
	}
	else if (token->tag == T_EXPANSION)
	{
		if (!find_variable(node, shell, token, index))
			return (-1);
		index++;
	}
	else if (is_command(token->tag))
	{
		node->command[index] = ft_strdup(token->content);
		if (!node->command[index])
			return (-1);
		index++;
	}
	else if (is_redirect(token->tag))
	{
		if (!add_redirect_token(node, token))
			return (-1);
	}
	return (index);
}

static t_token	*emplace_tokens(t_shell *shell, t_info **info, t_token *token)
{
	t_info	*node;
	size_t	index;

	index = 0;
	node = ft_calloc(1, sizeof(t_info));
	if (!node)
		return (NULL);
	node->command = ft_calloc(sizeof_node(&token) + 1, sizeof(char *));
	while (token && token->tag != T_PIPE && token->tag != T_NONE)
	{
		index = add_tokens_back(shell, node, token, index);
		if (index == -1)
			return (NULL /* Clean everything... */);
		token = token->next;
	}
	info_addback(info, node);
	return (token);
}

t_info	*parse_tokens(t_shell *shell, t_token **tokens)
{
	t_info		*info;
	t_token		*token;

	info = NULL;
	token = *tokens;
	if ((*tokens)->tag == T_NONE)
		return (NULL);
	while (token)
	{
		printf("Tag: %-16s : Content: %s\n",
			get_tag_name(token->tag), token->content);
		token = token->next;
	}
	token = *tokens;
	while (token)
	{
		token = emplace_tokens(shell, &info, token);
		if (token->tag == T_PIPE || token->tag == T_NONE)
			token = token->next;
	}
	return (info);
}

