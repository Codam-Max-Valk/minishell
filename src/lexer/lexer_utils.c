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
	if (!ft_istoken(s) || tag == 0 || tag >= 9) //TODO: Relook this code.
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
	if (tag == T_APPEND)
		return (2);
	if (tag == T_HERE_DOC)
		return (2);
	return (0);
}
