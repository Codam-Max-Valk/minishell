#include "../include/tokens.h"
#include "../include/libft.h"

const char	*get_tag_name(t_tag tag)
{
	const	char *(tag_table[100]) = {\
		[T_DOUBLE_QUOTE] = "Double Quote", \
		[T_SINGLE_QUOTE] = "Single Quote", \
		[T_REDIRECT_IN] = "Redirect In", \
		[T_REDIRECT_OUT] = "Redirect Out", \
		[T_PIPE] = "Pipe", \
		[T_APPEND] = "Append", \
		[T_HERE_DOC] = "Heredoc", \
		[T_EQUALS] = "Equals", \
		[T_EXPANSION] = "Expansions", \
		[T_SEMICOLUMN] = "Semi column", \
		[T_COMMAND] = "Command/Argument", \
		[T_NONE] = "None", \
	};

	if (!tag_table[tag])
		return ("Unrecognized token");
	return (tag_table[tag]);
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
	token = token_create(str1, tag);
	if (!token)
		return (free(str), free(str1), PARSE_FAILURE);
	token_addback(tokens, token);
	return (free(str), free(str1), length);
}

size_t	add_tagged_token(t_token **tokens, char *s, int i, t_tag tag)
{
	static int	length = 1;

	if (tag == T_SINGLE_QUOTE || tag == T_DOUBLE_QUOTE)
		length = tokenize(tokens, &s[i], tag, get_quote_length);
	else if (tag == T_HERE_DOC || tag == T_APPEND || tag == T_REDIRECT_IN || tag == T_REDIRECT_OUT)
		length = tokenize(tokens, &s[i], tag, get_redirect_length);
	else if (ft_issymbol(&s[i]))
		length = tokenize(tokens, &s[i], tag, get_symbol_length);
	else if (tag == T_EXPANSION)
		length = tokenize(tokens, &s[++i], tag, get_content_length) + 1;
	else if (ft_isexpander(&s[i]))
		length = tokenize(tokens, &s[i], T_EQUALS, get_expander_length);
	else if ((s[i] >= 33 && s[i] <= 126))
		length = tokenize(tokens, &s[i], T_COMMAND, get_content_length);
	else
		length = 1;
	return (length);
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
