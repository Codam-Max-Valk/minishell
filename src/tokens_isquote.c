#include "../include/tokens.h"

int	tag_isquote(t_tag tag)
{
	if (tag == T_SINGLE_QUOTE || tag == T_DOUBLE_QUOTE)
		return (1);
	return (0);
}

