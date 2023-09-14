#include "../include/tokens.h"
#include "../include/libft.h"

t_token	*token_create(char *arg, t_tag tag)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	if (arg)
	{
		token->content = ft_strdup(arg);
		if (!token->content)
			return (free(token), NULL);
	}
	token->tag = tag;
	token->next = NULL;
	return (token);
}

t_token	*token_dup(t_token *token)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	if (token->content)
	{
		new->content = ft_strdup(token->content);
		if (!new->content)
			return (NULL);
	}
	new->tag = token->tag;
	return (new);
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