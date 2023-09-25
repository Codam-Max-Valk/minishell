#include "../include/tokens.h"
#include "../include/libft.h"

t_tag	guess_tag(char *s)
{
	if (!s || !*s)
		return (0);
	if (ft_strncmp(s, APPEND, 2) == 0)
		return (T_APPEND);
	else if (ft_strncmp(s, HERE_DOC, 2) == 0)
		return (T_HERE_DOC);
	else if (ft_strncmp(s, PIPE, 1) == 0)
		return (T_PIPE);
	else if (ft_strncmp(s, DOUBLE_QUOTE, 1) == 0)
		return (T_DOUBLE_QUOTE);
	else if (ft_strncmp(s, SINGLE_QUOTE, 1) == 0)
		return (T_SINGLE_QUOTE);
	else if (ft_strncmp(s, REDIRECT_IN, 1) == 0)
		return (T_REDIRECT_IN);
	else if (ft_strncmp(s, REDIRECT_OUT, 1) == 0)
		return (T_REDIRECT_OUT);
	else if (ft_strncmp(s, EXPANSION, 1) == 0)
		return (T_EXPANSION);
	else if (ft_strncmp(s, SEMICOLUMN, 1) == 0)
		return (T_SEMICOLUMN);
	return (0);
}

int	get_token_length(t_tag tag)
{
	if (tag == T_REDIRECT_IN)
		return (1);
	if (tag == T_REDIRECT_OUT)
		return (1);
	if (tag == T_PIPE)
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

int	ft_istoken(char *s)
{
	const int	tag = guess_tag(s);

	if (!ft_isquote(*s))
		return (1);
	if (tag != T_DOUBLE_QUOTE || tag != T_SINGLE_QUOTE)
		return (1);
	if (tag != T_ARGUMENT || tag != T_COMMAND)
		return (1);
	return (0);
}

int	ft_issymbol(char *s)
{
	const t_tag tag = guess_tag(s);
	
	if (tag == T_REDIRECT_IN || tag == T_REDIRECT_OUT
		|| tag == T_APPEND || tag == T_HERE_DOC
		|| tag == T_PIPE || tag == T_SEMICOLUMN)
		return (1);
	return (0);
}

int	ft_isexpander(char *s)
{
	int		i;
	char	*str;

	i = 0;
	if (s[i] == '=' || !ft_strchr(s, '='))
		return (0);
	while (s[i]
		&& ft_strchr(&s[i], '=')
		&& !ft_issymbol(&s[i])
		&& !ft_isspace(s[i]))
		i++;
	str = ft_substr(s, 0, i);
	if (!str)
		return (0);
	if (!ft_strchr(str, '='))
		return (free(str), 0);
	return (free(str), 1);
}
