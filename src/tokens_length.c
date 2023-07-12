#include "../include/tokens.h"
#include "../include/libft.h"

int	get_token_length(t_tag tag)
{
	if (tag == redirect_in)
		return (1);
	if (tag == redirect_out)
		return (1);
	if (tag == pipe_icon)
		return (1);
	if (tag == append)
		return (2);
	if (tag == here_doc)
		return (2);

	return (0);
}
