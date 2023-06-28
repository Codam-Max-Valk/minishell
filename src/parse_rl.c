
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

char	*quote_token(t_tokens *tokens)
{
	 return (NULL);
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
