#include "minishell.h"
#include "tokens.h"

int	is_redirect(t_tag tag)
{
	if (tag == T_REDIRECT_IN || tag == T_REDIRECT_OUT)
		return (1);
	if (tag == T_APPEND || tag == T_HERE_DOC)
		return (1);
	return (0);
}

int	is_command(t_tag tag)
{
	if (tag == T_COMMAND)
		return (1);
	if (tag == T_SINGLE_QUOTE || tag == T_DOUBLE_QUOTE)
		return (1);
	return (0);
}
