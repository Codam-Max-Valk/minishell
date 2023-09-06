#include "../include/tokens.h"
#include "../include/libft.h"

t_token	*create_token(char *arg, t_tag tag)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = ft_strdup(arg);
	token->tag = tag;
	token->next = NULL;
	return (token);
}

void	token_addback(t_token **tokens, t_token *token)
{
	t_token	*node;

	node = NULL;
	if (!*tokens)
	{
		*tokens = token;
		return ;
	}
	node = *tokens;
	while (node->next)
		node = node->next;
	node->next = token;
}
