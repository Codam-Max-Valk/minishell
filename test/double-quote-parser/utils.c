#include "shell.h"

const char	*ft_readline(void)
{
	const char  *str = readline(PREFIX);

	if (!str)
		return (printf("exit\n"), exit(1), NULL);
	return (str);
}

void	print_tokens(t_list *lst)
{
	t_list	*tmp;
	t_token	*token;
	size_t	i;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		printf("Token (%d)\n", i);
		printf("%8s-> Content: %s\n", BOLD_GREEN, token->content);
		printf("%8s-> Length: %d\n", BOLD_GREEN, token->length);
		printf("%8s-> Tag: %d\n", BOLD_GREEN, token->tag);
		printf(RESET);
		i++;
		tmp = tmp->next;
	}
}
