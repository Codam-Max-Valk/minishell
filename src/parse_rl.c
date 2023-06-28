
#include "../include/minishell.h"
#include "../include/libft.h"

bool	find_special_char(t_tokens *tokens, char *spec_char)
{
	u_int32_t	i;

	i = 0;
	while (tokens->arguments[i])
	{
		if (strstr(tokens->arguments[i], spec_char))
			return (true);
		i++;
	}
	return (false);
}

char	**append_token(char	**tokens, char *new_tok)
{
	size_t	array_len;
	
	if (!new_tok)
		return (NULL);
	if (!tokens)
		return (ft_calloc(2, sizeof(char *)));
	while (tokens[array_len] != NULL)
		array_len++;
	tokens = ft_realloc(tokens, (array_len + 2) * sizeof(char *));
	if (!tokens)
		return (NULL);
	tokens[array_len] = new_tok;
	tokens[array_len + 1] = NULL;
	return(tokens);
}

char	*tokenize_quote(char *line, u_int32_t start, char quote_type)
{
	char	*token;

	u_int32_t	end;
	end = start + 1;
	while (line[end] != quote_type)
		end++;
	return (ft_substr(line, start, end - start));
}

char	**tmp_token(char *line)
{
	char	**tokens;
	u_int32_t i;

	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			append_token(tokens, tokenize_quote(line, i, line[i]));
	}
}

t_tokens	*tokenizer(char *read_line)
{
	t_tokens	*tokens;

	tokens = calloc(1, sizeof(t_tokens));
	if (!tokens)
		return (NULL);
	tokens->split_input = ft_split(read_line, ' ');
	if (!tokens->split_input)
		return (NULL);
	tokens->command = tokens->split_input[0];
	tokens->arguments = &tokens->split_input[1];
	if (find_special_char(tokens, "<"))
		tokens->redirect_in = true;
	if (find_special_char(tokens, ">"))
		tokens->redirect_out = true;
	if (find_special_char(tokens, "<<"))
		tokens->here_doc = true;
	if (find_special_char(tokens, ">>"))
		tokens->append = true;
	if (find_special_char(tokens, "|"))
		tokens->pipe = true;
	return (tokens);
}

int	maino()
{
	char a[] = "heya heyb heyc > out";
	t_tokens	*tokens;

	tokens = tokenizer(a);
	printf("split_input: ");
	for (int i = 0; tokens->split_input[i] != NULL; i++)
		printf("[%s], ", tokens->split_input[i]);
	printf("\ncommand: [%s]\narguments: ", tokens->command);
	for (int i = 0; tokens->arguments[i] != NULL; i++)
		printf("[%s], ", tokens->arguments[i]);
	printf("\nbools for redirect:\n in: %d\nout: %d\nappend: %d\nhere_doc: %d\n",
		tokens->redirect_in, tokens->redirect_out, tokens->append, tokens->here_doc);
	return (EXIT_SUCCESS);
}
