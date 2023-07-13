#include "../include/tokens.h"
#include "../include/libft.h"

t_tag	guess_tag(char *s)
{
	if (ft_strncmp(s, APPEND, 2) == 0)
		return (append);
	else if (ft_strncmp(s, HERE_DOC, 2) == 0)
		return (here_doc);
	else if (ft_strncmp(s, PIPE, 1) == 0)
		return (pipe_icon);
	else if (ft_strncmp(s, DOUBLE_QUOTE, 1) == 0)
		return (double_quote);
	else if (ft_strncmp(s, SINGLE_QUOTE, 1) == 0)
		return (single_quote);
	else if (ft_strncmp(s, REDIRECT_IN, 1) == 0)
		return (redirect_in);
	else if (ft_strncmp(s, REDIRECT_OUT, 1) == 0)
		return (redirect_out);
	else if (ft_strncmp(s, ARGUMENT, 1) == 0)
		return (argument);
	return (0);
}

t_token	*create_token(char *arg, t_tag tag)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	if (tag != argument)
		token->is_token = true;
	else
		token->is_command = true;
	token->content = ft_strdup(arg);
	token->tag = tag;
	return (token);
}

void	token_addback(t_token **tokens, t_token *token)
{
	t_token	*node;

	if (!*tokens)
	{
		*tokens = node;
		return ;
	}
	node = *tokens;
	while (node->next)
		node = node->next;
	node->next = token;
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

char	*substr_quote(char *s, int (*is_quote)(char))
{
	size_t	len;
	char	*str;

	len = 1;
	while (!is_quote(s[len]) && s[len] != '\0')
		len++;
	if (is_quote(s[len]))
		len++;
	else
		return (NULL);
	str = ft_substr(s, 0, len);
	return (str);
}

int	tokenize_quote(t_token **tokens, char *s)
{
	char	*str;
	//Add the token to the back.

	if (ft_issemiquote(*s))
		str = substr_quote(s, ft_issemiquote);
	else
		str = substr_quote(s, ft_isdoublequote);
	return (ft_strlen(str));
}

int	tokenize_symbol(t_token	*tokens, char *s)
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
		return (free(str), -1);
	ft_printf("Substr: %s\n", str);
	new = create_token(str, tag);
	if (!new)
		return (free(str), -1);
	token_addback(&tokens, new);
	return (free(str), str_length);
}

size_t	tokenize_command(t_token *tokens, char *s)
{
	char		*command;
	size_t		i;
	size_t		len;

	i = 0;
	len = 0;
	while (s[len] && !ft_isspace(s[len]))
		len++;
	
	ft_printf("%s => Command Length: %d\n", ft_substr(s, 0, len), len);
	
	return (len);
}

t_token	*tokenizer2(char *s)
{
	t_token	*tokens;
	t_tag	tag;
	size_t	index;

	index = 0;
	tokens = NULL;
	while (s[index])
	{
		tag = guess_tag(&s[index]);
		if (tag >= 1)
			ft_printf("Guessed tag is: (%c) %d -> Tag: %d\n", s[index], index, tag);
		if (tag == single_quote || tag == double_quote) //TODO Add more logic.
			index += tokenize_quote(&tokens, &s[index]);
		if (tag >= redirect_in && tag <= here_doc) //Maak het standaard dat het detect voor elke token behalve edge cases.
			index += tokenize_symbol(tokens, &s[index]); //Tokenize symbol returns -1 if it fails.
		else if (!tag && (s[index] >= 33 && s[index] <= 126))
			index += tokenize_command(tokens, &s[index]);
		else if (tag == argument)
			//blablabla
		else
			index++;
	}
	ft_printf("\n");
	return (tokens);
}

void	free_token(t_token	*token)
{
	free(token);
}

int main()
{
	t_token *tokens = tokenizer2("echo \"Hello \'Boys\'\" |cat -e>out>>out2 ");

	if (!tokens)
		return (printf("List is empty\n"));
	for(tokens; tokens->next; tokens = tokens->next)
		ft_printf("%s (%d)\n", tokens->content, tokens->tag);
}

void pipe_check()
{


	t_token t;

	if (t.tag == pipe)
	{
		
	}

}
