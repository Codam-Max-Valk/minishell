
#include "../include/minishell.h"
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

size_t append_token_len(t_token ***token_arr, t_token *new_tok)
{
	size_t arr_len = 0;

	if (!new_tok)
		return 0;
	if (!(*token_arr))
	{
		*token_arr = ft_calloc(2, sizeof(t_token *));
		if (!(*token_arr))
			return 0;
	}
	while ((*token_arr)[arr_len] != NULL)
		arr_len++;
	*token_arr = ft_realloc(*token_arr, (arr_len + 2) * sizeof(t_token *));
	if (!(*token_arr))
		return 0;
	(*token_arr)[arr_len] = new_tok;
	(*token_arr)[arr_len + 1] = NULL;
	return (ft_strlen((*token_arr)[arr_len]->token));
}

t_token	*tokenize_quote(char *line, u_int32_t start, char quote_type)
{
	t_token		*token;
	u_int32_t	end;

	end = start + 1;
	while (line[end] != quote_type)
		end++;
	end++;
	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->token = ft_substr(line, start, end - start);
	if (!token->token)
		return (NULL);
	token->tag = quote_type;
	return (token);
}

t_token	*tokenize_string(char *read_line, t_tag tag)
{
	t_token	*token;
	size_t	len;

	len = 0;
	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	while (!ft_strchr(DELIM, read_line[len]))
		len++;
	token->token = ft_substr(read_line, 0, len);
	token->tag = tag;
	return (token);
}

t_token	*custom_token(char *string, t_tag tag)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->token = string;
	token->tag = tag;
	return (token);
}

t_token	**tokenizer(char *read_line)
{
	t_token		**tokens;
	size_t		i;
	t_tag		tag;

	i = 0;
	tokens = NULL;
	while (read_line[i])
	{
		tag = guess_tag(&read_line[i]);
		ft_printf("char line %d: %c\n", i, read_line[i]);
		if (tag == append)
		 	i += append_token_len(&tokens, custom_token(">>", tag));
		else if (tag == here_doc)
		 	i += append_token_len(&tokens, custom_token("<<", tag));
		else if (tag == single_quote || tag == double_quote)
			i += append_token_len(&tokens, tokenize_quote(read_line, i, read_line[i]));
		else if (tag == redirect_in)
			i += append_token_len(&tokens, custom_token("<", tag));
		else if (tag == redirect_out)
			i += append_token_len(&tokens, custom_token(">", tag));
		else if (tag == pipe_icon)
			i += append_token_len(&tokens, custom_token("|", tag));
		else if (ft_isprint(read_line[i]) && !ft_isspace(read_line[i]))
			i += append_token_len(&tokens, tokenize_string(&read_line[i], tag));
		else if (ft_isspace(read_line[i]))
			i++;
		ft_printf("Tag: %d\n", tag);
	}
	return (tokens);
}
