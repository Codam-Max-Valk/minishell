#include "../include/tokens.h"
#include "../include/libft.h"

const char	*get_tag_name(t_tag tag)
{
	if (tag == T_DOUBLE_QUOTE)
		return ("DOUBLE_QUOTE");
	else if (tag == T_SINGLE_QUOTE)
		return ("SINGLE_QUOTE");
	else if (tag == T_REDIRECT_IN)
		return ("REDIRECT_IN");
	else if (tag == T_REDIRECT_OUT)
		return ("REDIRECT_OUT");
	else if (tag == T_PIPE)
		return ("PIPE");
	else if (tag == T_APPEND)
		return ("APPEND");
	else if (tag == T_HERE_DOC)
		return ("HERE_DOC");
	else if (tag == T_EQUALS)
		return ("EQUALS");
	else if (tag == T_EXPANSION)
		return ("EXPANSION");
	else if (tag == T_SEMICOLUMN)
		return ("SEMICOLUMN");
	else if (tag == T_COMMAND)
		return ("COMMAND");
	return ("NONE");
}

static int	tokenize(t_token **tokens, char *s, t_tag tag, t_token_lengthfunc f)
{
	t_token	*token;
	char	*str;
	char	*str1;
	int		length;

	length = f(s);
	if (length == -1)
		return (PARSE_FAILURE);
	if (length == 2 && (tag == T_SINGLE_QUOTE || tag == T_DOUBLE_QUOTE))
		return (length);
	str = ft_substr(s, 0, length);
	if (!str)
		return (PARSE_FAILURE);
	str1 = ft_strtrim(str, DELIMITOR);
	if (!str1)
		return (free(str), PARSE_FAILURE);
	token = create_token(str1, tag);
	if (!token)
		return (PARSE_FAILURE);
	token_addback(tokens, token);
	return (free(str), length);
}

t_token	*tokenizer2(char *s)
{
	t_token	*tokens;
	t_tag	tag;
	size_t	index;
	int		x;

	index = 0;
	tokens = NULL;
	while (s[index])
	{
		tag = guess_tag(&s[index]);
		if (tag == T_SINGLE_QUOTE || tag == T_DOUBLE_QUOTE)
			x = tokenize(&tokens, &s[index], tag, get_quote_length);
		else if (tag == T_HERE_DOC || tag == T_APPEND || tag == T_REDIRECT_IN || tag == T_REDIRECT_OUT)
			x = tokenize(&tokens, &s[index], tag, get_redirect_length);
		else if (ft_issymbol(tag))
			x = tokenize(&tokens, &s[index], tag, get_symbol_length);
		else if (tag == T_EXPANSION)
			x = tokenize(&tokens, &s[++index], T_EXPANSION, get_content_length);
		else if (s[index] >= 33 && s[index] <= 126)
			x = tokenize(&tokens, &s[index], T_COMMAND, get_content_length);
		else
			x = 1;
		if (x >= 1)
			index += x;
		else
			return (token_lstclear(&tokens, token_free), NULL);
	}
	token_addback(&tokens, create_token("NONE", T_END)); //Solid cliphanger to make this code function temporary
	return (tokens);
}
