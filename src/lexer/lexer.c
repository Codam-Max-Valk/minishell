#include "../include/tokens.h"
#include "../include/libft.h"

int	tokenize(t_token **tokens, char *s, t_tag tag, int (*f)(char *))
{
	t_token	*token;
	char	*str;
	int		length;

	length = f(s); //Length functions can return their own error
	if (length == -1)
		return (PARSE_FAILURE); //Error when lengths couldn't be calculated
	str = ft_substr(s, 0, length);
	if (!str)
		return (PARSE_FAILURE); //Malloc error
	token = create_token(str, tag);
	if (!token)
		return (PARSE_FAILURE); //Malloc error
	token_addback(tokens, token);
	return (length);
}

t_token	*tokenizer2(char *s)
{
	t_token	*tokens;
	t_tag	tag;
	size_t	index;
	int	result;

	index = 0;
	result = 0;
	tokens = NULL;
	while (s[index]) //TODO: Add result checking and freeing.
	{
		tag = guess_tag(&s[index]);
		if (tag == T_SINGLE_QUOTE || tag == T_DOUBLE_QUOTE)
			result = tokenize(&tokens, &s[index], tag, get_quote_length);
		else if (tag == T_REDIRECT_IN || tag == T_REDIRECT_OUT || tag == T_APPEND || tag == T_HERE_DOC || tag == T_PIPE_ICON)
			result = tokenize(&tokens, &s[index], tag, get_symbol_length);
		else if (tag == T_ARGUMENT || (s[index] >= 33 && s[index] <= 126))
			result = tokenize(&tokens, &s[index], T_COMMAND, get_content_length);
		else
			result = 1;
		if (result >= 1)
			index += result;
		else
			return (NULL);
		
	}
	return (tokens);
}

void	free_token(t_token	*token)
{
	free(token);
}

int main()
{
	//t_token *tokens = tokenizer2("echo \"Hello \'Boys\'\" | cat -e > out >> out2");
	t_token *tokens = tokenizer2("echo\"Hello \'Boys|cat -e>out>>out2");

	if (!tokens)
		return (printf("List is empty\n"));
	while (tokens->next)
	{
		ft_printf("TAG: %d\t\t:\tCONTENT: %s\n", tokens->tag, tokens->content);
		tokens = tokens->next;
	}
}
