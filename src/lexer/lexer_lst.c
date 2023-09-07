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

size_t	token_lstsize(t_token *token)
{
	size_t	size;

	size = 0;
	while (token->next)
	{
		size++;
		token = token->next;
	}
	return (size);
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

void	token_lstclear(t_token **tokens, t_token_clearfunc func)
{
	//Clear all tokens.
	t_token	*index;
	t_token	*temp;

	index = *tokens;
	while (index->next)
	{
		temp = index->next;
		func(index);
		index = temp;
	}
	*tokens = NULL;
}

void	token_free(t_token *token)
{
	free(token->content);
	free(token);
}