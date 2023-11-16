#include "tokens.h"
#include "minishell.h"
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
	if (length <= 2 && (tag == T_SINGLE_QUOTE || tag == T_DOUBLE_QUOTE))
	{
		return (length);
	}
	if (tag == T_COMMAND)
	{
		printf("Potetioniol ocmmand: %s\n", ft_replaceall(s, '\''));
	}
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
	const int	(*funcmap[11])(char *) = {
	[T_DOUBLE_QUOTE] = get_quote_length,
	[T_SINGLE_QUOTE] = get_quote_length,
	[T_REDIRECT_IN] = get_redirect_length,
	[T_REDIRECT_OUT] = get_redirect_length,
	[T_APPEND] = get_redirect_length,
	[T_HERE_DOC] = get_redirect_length,
	[T_PIPE] = get_symbol_length,
	[T_SEMICOLUMN] = get_symbol_length,
	};

	if (tag == T_SINGLE_QUOTE || tag == T_DOUBLE_QUOTE || ft_issymbol(&s[i]))
		return (tokenize(tokens, &s[i], tag, funcmap[tag]));
	else if (tag == T_EXPANSION)
		return (tokenize(tokens, &s[++i], tag, get_content_length) + 1);
	else if (ft_isexpander(&s[i]))
		return (tokenize(tokens, &s[i], T_EQUALS, get_expander_length));
	else if ((s[i] >= 33 && s[i] <= 126))
		return (tokenize(tokens, &s[i], T_COMMAND, get_content_length));
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
	token_addback(&tokens, token_create(NULL, 0)); //Solid cliphanger to make this code function temporary
	return (tokens);
}

void	token_free(t_token *token)
{
	free(token->content);
	free(token);
}
