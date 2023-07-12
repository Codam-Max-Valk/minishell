#include "../include/tokens.h"

int	tag_isquote(t_tag tag)
{
	if (tag == single_quote || tag == double_quote)
		return (1);
	return (0);
}

