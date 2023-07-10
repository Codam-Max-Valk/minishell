
#include "../include/minishell.h"
#include "../include/libft.h"

char	**ft_token_to_char_arr_n(t_token ***t1, size_t n)
{
	char	**ptr;
	size_t	i;

	i = 0;
	ptr = calloc(n + 1, sizeof(char **));
	if (!(ptr))
		return (0);
	while ((*t1)[i] != NULL && i < n)
	{
		ptr[i] = (*t1)[i]->token;
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}
/*
int main(int ac, char **av)
{
	t_token **token;
	char **test;
	size_t i = 0;

	token = calloc(ac - 1, sizeof(t_token *));
	if (!token)
		return 1;
	while (av[i])
	{
		token[i] = malloc(sizeof(t_token));
		if (!token[i])
			return 1;
		token[i]->token = av[i];
		i++;
	}
	test = ft_token_to_char_arr_n(&token, i);
	for (int j = 0; j < i; j++)
		printf("token %d: %s\n", j, test[j]);
	free(test);
	for (int j = 0; j < i; j++)
		free(token[j]);
	free(token);
	system ("leaks -q a.out");
	return 0;
}*/
