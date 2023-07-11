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

void	*create_token(char *arg, t_tag tag)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	if (tag != argument)
	{
		token->is_token = true;
	}

	if (tag == argument)
	{
		token->is_command = true;
	}
	return (token);
}

int		split_quote(char *s)
{
	size_t	len;

	len = 0;
	ft_printf("Quote: %s\n", s);
	while (s[len] != ft_isquote(s[len]) && s[len])
		len++;
	ft_printf("Length is: %d\n", len);
	return (len);
}

int	ft_istoken(char *s)
{
	const int tag = guess_tag(s);

	if (!ft_isquote(*s))
		return (1);
	if (tag != 0 || tag >= 9)
		return (1);
	return (0);
}

size_t	tokenize_command(char *s)
{
	char		*command;
	size_t		i;
	size_t		len;

	i = 0;
	len = 0;
	while (s[len] && !ft_istoken(&s[len]))
		len++;
	while (s[i] && !ft_isquote(s[i]))
		i++;
	if (ft_istoken(&s[i]))
		ft_printf("the command does not have quotes... 2 probabilities: Either - or it is an echo / grep.\n");
	else
	{
		command = ft_substr(s, 0x00, len);
		command = ft_strtrim(command, " \t\n\v\r\f");
		ft_printf("Command: %s", command);
		 //TODO Write a new split that splits till the token...
	}
	
	return (len);
}

int	ft_has_tokens(char *s)
{
	size_t	i;
	bool	open;
	bool	closed;

	i = 0;
	closed = false;
	while (s[i] != ft_istoken(&s[i]) || s[i])
	{
		if (ft_isquote(s[i]) && !open)
			open = true;
		if (ft_isquote(s[i]) && !open)
			closed = true;
		i++;
	}
	return ((open & closed) == 1);
}

t_token	*tokenizer2(char *s)
{
	t_token	*tokens;
	t_tag	tag;
	size_t	index;

	index = 0;
	while (s[index])
	{
		tag = guess_tag(&s[index]);
		ft_printf("Guessed tag is: (%s) %d\n", &s[index], index);
		if (ft_isprint(s[index]) && !ft_istoken(&s[index + 1]))
		{
			ft_printf("Misschien wel een commando :O\n");
			tokenize_command(&s[index]);
		}
		index++;
	}

	return (tokens);
}

void	free_token(t_token	*token)
{
	free(token);
}

int main()
{
	t_token *tokens = tokenizer2("echo \"LOL!\"");
	bool test = false;

	if (test)
	{
		for(t_token *node = tokens; node->next; node = node->next)
			ft_printf("%s (%d)", node->content, node->tag);
	}
}
