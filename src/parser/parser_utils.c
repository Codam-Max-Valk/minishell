#include "tokens.h"

int	sizeof_node(t_token **tokens)
{
	int		i;
	t_token	*token;

	i = 0;
	token = *tokens;
	while (token->tag != T_PIPE
		&& token->tag != T_NONE
		&& token)
	{
		if (token->tag == T_COMMAND
			|| token->tag == T_EXPANSION
			|| token->tag == T_EQUALS
			|| token->tag == T_DOUBLE_QUOTE
			|| token->tag == T_SINGLE_QUOTE)
		i++;
		token = token->next;
	}
	return (i);
}

