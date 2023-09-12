#include "../include/tokens.h"
#include "../include/libft.h"

int	get_quote_length(char *s)
{
	char	type;
	int		length;
	int		hit;

	if (!s || !*s)
		return (PARSE_FAILURE);
	hit = 0;
	type = *s;
	length = 1;
	while (s[length] && !hit)
	{
		if (s[length] == type)
			hit++;
		length++;
	}
	if (!hit)
		return (ft_printf("> Unclosed quotes\n"), PARSE_FAILURE);
	return (length);
}

int	get_symbol_length(char *s)
{
	const t_tag	tag = guess_tag(s);
	int			length;

	length = 0;
	if (!s || !*s)
		return (PARSE_FAILURE);
	if (!ft_istoken(s) || !ft_issymbol(tag))
		return (PARSE_FAILURE);
	length = get_token_length(tag);
	if (length <= 0)
		return (PARSE_FAILURE);
	return (length);
}

int get_redirect_length(char *s)
{
	int	length;

	length = 0;
	if (!s || !*s)
		return (PARSE_FAILURE);
	while (s[length] && s[length] >= 32 && s[length] <= 126 && ft_istoken(&s[length]))
		length++;
	ft_printf("Length: %d\n", length);
	return (length);
}

int	get_content_length(char *s)
{
	int	length;

	length = 0;
	if (!s || !*s)
		return (PARSE_FAILURE);
	while (s[length] && !ft_isspace(s[length]) && !guess_tag(&s[length]))
		length++;
	return (length);
}

int	get_token_length(t_tag tag)
{
	if (tag == T_REDIRECT_IN)
		return (1);
	if (tag == T_REDIRECT_OUT)
		return (1);
	if (tag == T_PIPE)
		return (1);
	if (tag == T_EQUALS)
		return (1);
	if (tag == T_EXPANSION)
		return (1);
	if (tag == T_SEMICOLUMN)
		return (1);
	if (tag == T_APPEND)
		return (2);
	if (tag == T_HERE_DOC)
		return (2);
	return (0);
}
