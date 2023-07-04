
#include "../include/minishell.h"
#include "../include/libft.h"

t_tag	char_tag(char *input)
{
	t_tag		tag;

	tag = 0;
	// if (strncmp(input, ">>", 2))
	// 	tag = append;
	// else if (strncmp(input, "<<", 2))
	// 	tag = here_doc;
	if (strncmp(input, "<", 1) == 0)
		tag = redirect_in;
	else if (strncmp(input, ">", 1) == 0)
		tag = redirect_out;
	else if (strncmp(input, "|", 1) == 0)
		tag = pipe_icon;
	// printf("tag: %i\n", tag);
	return (tag);
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
	return ft_strlen((*token_arr)[arr_len]->token);
}


// size_t append_token_len(t_token **token_arr, t_token *new_tok)
// {
// 	size_t	arr_len;
	
// 	if (!new_tok)
// 		return (0);
// 	if (!token_arr)
// 		token_arr = ft_calloc(2, sizeof(t_token));
// 	while (token_arr[arr_len] != NULL)
// 		arr_len++;
// 	token_arr = realloc(token_arr, (arr_len + 2) * sizeof(t_token));
// 	if (!token_arr)
// 		return (0);
// 	token_arr[arr_len] = new_tok;
// 	token_arr[arr_len + 1] = NULL;
// 	return(ft_strlen(token_arr[arr_len]->token));
// }

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
	printf("token quote: %s\n", token->token);
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
	// printf("token %s\n", token->token);
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
	// printf("token %s\n", token->token);
	return (token);
}

t_token	**tokenizer(char *read_line)
{
	t_token		**tokens;
	size_t		i;
	size_t		j;
	t_tag		tag;

	i = 0;
	j = ft_strlen(read_line);
	tokens = NULL;
	while (i < j)
	{
		tag = 0;
		// if (tag == append)
		// 	append_handling();
		// if (tag == here_doc)
		// 	here_handling();
		if (read_line[i] == '\'' || read_line[i] == '\"')
			i += append_token_len(&tokens, tokenize_quote(read_line, i, read_line[i]));
		else if (read_line[i] == '<')
			i += append_token_len(&tokens, custom_token("<", char_tag(&read_line[i])));
		else if (read_line[i] == '>')
			i += append_token_len(&tokens, custom_token(">", char_tag(&read_line[i])));
		else if (read_line[i] == '|')
			i += append_token_len(&tokens, custom_token("|", char_tag(&read_line[i])));
		else if (ft_isprint(read_line[i]) && !ft_isspace(read_line[i]))
			i += append_token_len(&tokens, tokenize_string(&read_line[i], char_tag(&read_line[i])));
		else if (ft_isspace(read_line[i]))
			i++;
	}
	return (tokens);
}

// int main()
// {
// 	char	*test = "ls -la |'grep' Mak\"e|\"cat>o0 -e";
// 	t_token	**tokens = NULL;
// 	int i = 0;

// 	tokens = tokenizer(test);
// 	for (int i = 0; tokens[i]; i++){
// 		printf("token %d: %s\t", i, tokens[i]->token);
// 		printf("tag %c\n", tokens[i]->tag);
// 		}
// 	return (0);
// }
