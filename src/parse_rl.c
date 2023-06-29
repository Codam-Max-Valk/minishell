
#include "../include/minishell.h"
#include "../include/libft.h"

t_tag	char_tag(char *input)
{
	t_tag		tag;

	tag = 0;
	if (strnstr(input, ">>", 2))
		tag = append;
	else if (strnstr(input, "<<", 2))
		tag = here_doc;
	else if (strnstr(input, "<", 1))
		tag = redirect_in;
	else if (strnstr(input, ">", 1))
		tag = redirect_out;
	else if (strnstr(input, "|", 1))
		tag = pipe;
	return (tag);
}

size_t append_token_len(t_token **token_arr, t_token *new_tok)
{
	size_t	arr_len;
	
	if (!new_tok)
		return (NULL);
	if (!token_arr)
		return (ft_calloc(2, sizeof(t_token)));
	while (token_arr[arr_len] != NULL)
		arr_len++;
	token_arr = ft_realloc(token_arr, (arr_len + 2) * sizeof(t_token));
	if (!token_arr)
		return (NULL);
	token_arr[arr_len] = new_tok;
	token_arr[arr_len + 1] = NULL;
	return(token_arr);
}

t_token	*tokenize_quote(char *line, u_int32_t start, char quote_type)
{
	t_token		*token;
	u_int32_t	end;

	end = start + 1;
	while (line[end] != quote_type)
		end++;
	token->token = ft_substr(line, start, end - start);
	if (!token->token)
		return (NULL);
	token->tag = argument;
	return (token);
}

t_tokens	**tokenizer(char *read_line)
{
	t_tokens	**tokens;
	size_t		i;
	t_tag		tag;


	*tokens = calloc(2, sizeof(t_tokens));
	if (!*tokens)
		return (NULL);
	while (read_line[i])
	{
		tag = char_tag(&read_line[i]);
		if (tag == here_doc)
			here_handling();
		if (tag == redirect_in || tag == redirect_out)


			
	}
	return (tokens);
}


