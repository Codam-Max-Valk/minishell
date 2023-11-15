#include "tokens.h"
#include "libft.h"

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
	token = token_create(str1, tag);
	if (!token)
		return (free(str), free(str1), PARSE_FAILURE);
	token_addback(tokens, token);
	return (free(str), free(str1), length);
}

size_t	add_tagged_token(t_token **tokens, char *s, int i, t_tag tag)
{
	if (tag == T_SINGLE_QUOTE || tag == T_DOUBLE_QUOTE)
	{
		return (tokenize(tokens, &s[i], tag, get_quote_length));
	}
	else if (tag == T_HERE_DOC || tag == T_APPEND || tag == T_REDIRECT_IN || tag == T_REDIRECT_OUT)
	{
		return (tokenize(tokens, &s[i], tag, get_redirect_length));
	}
	else if (ft_issymbol(&s[i]))
	{
		return (tokenize(tokens, &s[i], tag, get_symbol_length));
	}
	else if (tag == T_EXPANSION)
	{
		return (tokenize(tokens, &s[++i], tag, get_content_length) + 1);
	}
	else if (ft_isexpander(&s[i]))
	{
		return (tokenize(tokens, &s[i], T_EQUALS, get_expander_length));
	}
	else if ((s[i] >= 33 && s[i] <= 126))
	{
		return (tokenize(tokens, &s[i], T_COMMAND, get_content_length));
	}
	return (1);
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
		x = add_tagged_token(&tokens, s, index, tag);
		if (x >= 1)
		{
			index += x;
			tokens->size++;
		}
		else
			return (token_lstclear(&tokens, token_free), NULL);
	}
	return (tokens);
}

void	token_free(t_token *token)
{
	free(token->content);
	free(token);
}
