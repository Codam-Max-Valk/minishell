#include "../include/tokens.h"
#include "../include/libft.h"

int	get_token_length(t_tag tag)
{
	if (tag == T_REDIRECT_IN)
		return (1);
	if (tag == T_REDIRECT_OUT)
		return (1);
	if (tag == T_PIPE_ICON)
		return (1);
	if (tag == T_APPEND)
		return (2);
	if (tag == T_HERE_DOC)
		return (2);
	return (0);
}

t_tag	guess_tag(char *s)
{
	if (ft_strncmp(s, APPEND, 2) == 0)
		return (T_APPEND);
	else if (ft_strncmp(s, HERE_DOC, 2) == 0)
		return (T_HERE_DOC);
	else if (ft_strncmp(s, PIPE, 1) == 0)
		return (T_PIPE_ICON);
	else if (ft_strncmp(s, DOUBLE_QUOTE, 1) == 0)
		return (T_DOUBLE_QUOTE);
	else if (ft_strncmp(s, SINGLE_QUOTE, 1) == 0)
		return (T_SINGLE_QUOTE);
	else if (ft_strncmp(s, REDIRECT_IN, 1) == 0)
		return (T_REDIRECT_IN);
	else if (ft_strncmp(s, REDIRECT_OUT, 1) == 0)
		return (T_REDIRECT_OUT);
	return (0);
}

int	ft_istoken(char *s)
{
	const int	tag = guess_tag(s);

	if (!ft_isquote(*s))
		return (1);
	if (tag >= 1 || tag <= 8)
		return (1);
	return (0);
}

int	tag_isquote(t_tag tag)
{
	if (tag == T_SINGLE_QUOTE || tag == T_DOUBLE_QUOTE)
		return (1);
	return (0);
}

///////////////////////////////////////////////////////////////////////////

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

bool	try_addtoken(t_token **tokens, char *arg, t_tag tag)
{
	t_token	*token;

	token = create_token(arg, tag);
	if (!token)
		return (free(token->content), free(token), false);
	token_addback(tokens, token);
	return (true);
}

static int	tokenize_quote(t_token **tokens, char *s, char type)
{
	char	*str;
	int		length;
	int		hit;
	t_tag	tag;

	length = 1;
	hit = 0;
	tag = guess_tag(&type);
	while(s[length] && !hit)
	{
		if (s[length] == type)
			hit++;
		length++;
	}
	if (!hit)
		return (ft_printf("> Unclosed quotes"), 1);
	str = ft_substr(s, 0, length);
	if (!str)
		return (free(str), -1);
	if (!try_addtoken(tokens, str, tag))
		return (free(str), -1);
	return (length);
}

static size_t	tokenize_symbol(t_token	**tokens, char *s)
{
	const t_tag	tag = guess_tag(s);
	t_token	*new;
	char	*str;
	size_t	str_length;

	if (!ft_istoken(s) || tag == 0 || tag >= 9)
		return (-1);	
	
	str_length = get_token_length(tag);
	if (str_length == 0)
		return (-1);
	
	str = ft_substr(s, 0, str_length);
	if (!str)
		return (-1);

	if (!try_addtoken(tokens, str, tag))
		return (free(str), -1);
	return (free(str), str_length);
}

static size_t	tokenize_content(t_token **tokens, char *s)
{
	char		*str;
	size_t		i;
	size_t		len;

	i = 0;
	len = 0;
	while (s[len] && !ft_isspace(s[len]))
		len++;
	
	str = ft_substr(s, 0, len);
	if (!str)
		return (0);

	if (!try_addtoken(tokens, str, T_COMMAND))
		return (free(str), -1);
	return (len);
}

t_token	*tokenizer2(char *s)
{
	t_token	*tokens;
	t_tag	tag;
	size_t	result;
	size_t	index;

	index = 0;
	tokens = NULL;
	while (s[index])
	{
		tag = guess_tag(&s[index]);
		//if (tag >= 1)
		//	ft_printf("Guessed tag is: (%c) %d -> Tag: %d\n", s[index], index, tag);
		if (tag == T_SINGLE_QUOTE || tag == T_DOUBLE_QUOTE)
			result = tokenize_quote(&tokens, &s[index], s[index]);
		else if (tag == T_REDIRECT_IN || tag == T_REDIRECT_OUT || tag == T_APPEND || tag == T_HERE_DOC)
			result = tokenize_symbol(&tokens, &s[index]);
		else if (tag == T_ARGUMENT || (s[index] >= 33 && s[index] <= 126))
			result = tokenize_content(&tokens, &s[index]);
		else
			result = 1;
		if (result >= 1)
			index += result;
		else
			break ;
	}
	return (tokens);
}

void	free_token(t_token	*token)
{
	free(token);
}

//int main()
//{
//	//t_token *tokens = tokenizer2("echo \"Hello \'Boys\'\" | cat -e > out >> out2");
//	t_token *tokens = tokenizer2("echo \"Hello \'Boys\" | cat -e > out >> out2");

//	if (!tokens)
//		return (printf("List is empty\n"));
//	ft_printf("Content: %s\n", tokens->content);
//	while (tokens->next)
//	{
//		ft_printf("TAG: %d\t=>\tCONTENT: %s\n", tokens->tag, tokens->content);
//		tokens = tokens->next;
//	}
//}
