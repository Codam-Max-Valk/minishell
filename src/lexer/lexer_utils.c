#include "../include/tokens.h"
#include "../include/libft.h"

int	get_quote_length(char *s)
{
	int	length;
	char	type;
	int		hit;

	hit = 0;
	type = *s;
	length = 1;
	while(s[length] && !hit)
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
	int		length;

	length = 0;
	if (!ft_istoken(s) || tag == 0 || tag >= 9)
		return (PARSE_FAILURE);
	length = get_token_length(tag);
	if (length <= 0)
		return (PARSE_FAILURE);
	return (length);
}

int	get_content_length(char *s)
{
	int	length;

	length = 0;
	while (s[length] && !ft_isspace(s[length]) && !guess_tag(&s[length]))
		length++;
	return (length);
}
