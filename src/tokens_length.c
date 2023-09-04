#include "../include/tokens.h"
#include "../include/libft.h"

int	get_token_length(t_tag tag)
{
	if (tag == T_REDIRECT_IN)
		return (1);
	if (tag == T_REDIRECT_OUT)
		return (1);
	if (tag == pipe_icon)
		return (1);
	if (tag == T_APPEND)
		return (2);
	if (tag == T_HERE_DOC)
		return (2);

	return (0);
}
