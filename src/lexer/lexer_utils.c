#include "tokens.h"
#include "libft.h"

int	get_quote_length(char *s)
{
	char	type;
	short	hit;
	int		length;

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
		return (ft_printf("error: unclosed quotes\n"), PARSE_FAILURE);
	return (length);
}

int	get_redirect_length(char *s)
{
	const t_tag	tag = guess_tag(s);
	int			index;
	size_t		length;

	length = 0;
	if (!s || !*s || !tag)
		return (PARSE_FAILURE);
	index = get_token_length(tag);
	while (ft_isspace(s[index]))
		index++;
	while (s[index]
		&& !ft_isspace(s[index])
		&& !ft_issymbol(&s[index]))
	{
		length++;
		index++;
	}
	if (!length)
		return (ft_printf("error: missing file name\n"), PARSE_FAILURE);
	return (index);
}

int	get_content_length(char *s)
{
	int	length;

	length = 0;
	if (!s || !*s)
		return (PARSE_FAILURE);
	while (s[length]
		&& !ft_isspace(s[length])
		&& !ft_issymbol(&s[length]))
		length++;
	return (length);
}

