#include "../include/tokens.h"
#include "../include/libft.h"


int	get_token_length(t_tag tag)
{
	if (tag == T_REDIRECT_IN)
		return (1);
	if (tag == T_REDIRECT_OUT)
		return (1);
	if (tag == T_PIPE_ICON)
		return (1);
	if (tag == T_APPEND)
		return (2);
	if (tag == T_HERE_DOC)
		return (2);
	return (0);
}

t_tag	guess_tag(char *s)
{
	if (ft_strncmp(s, APPEND, 2) == 0)
		return (T_APPEND);
	else if (ft_strncmp(s, HERE_DOC, 2) == 0)
		return (T_HERE_DOC);
	else if (ft_strncmp(s, PIPE, 1) == 0)
		return (T_PIPE_ICON);
	else if (ft_strncmp(s, DOUBLE_QUOTE, 1) == 0)
		return (T_DOUBLE_QUOTE);
	else if (ft_strncmp(s, SINGLE_QUOTE, 1) == 0)
		return (T_SINGLE_QUOTE);
	else if (ft_strncmp(s, REDIRECT_IN, 1) == 0)
		return (T_REDIRECT_IN);
	else if (ft_strncmp(s, REDIRECT_OUT, 1) == 0)
		return (T_REDIRECT_OUT);
	return (0);
}

int	ft_istoken(char *s)
{
	const int	tag = guess_tag(s);

	if (!ft_isquote(*s))
		return (1);
	if (tag != T_ARGUMENT || tag != T_COMMAND)
		return (1);
	return (0);
}

int	tag_isquote(t_tag tag)
{
	if (tag == T_SINGLE_QUOTE || tag == T_DOUBLE_QUOTE)
		return (1);
	return (0);
}
