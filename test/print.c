#include "testshell.h"
#include "colors.h"

void	print_token(t_token *token)
{
	printf("%-6s-> Content: %s\n", GREEN, token->content);
	printf("%-6s-> Size: %d\n", GREEN, *(token->size));
	printf("%-6s-> Type: %d\n", GREEN, token->type);
	printf("%s", RESET);
}

void	print_token_list(t_token *token)
{
	int	i;
	int	size;
	
	if (!token || !token[0].content)
		return ;
	i = 0;
	size = *(token[2].size);
	printf("Token list size: %d\n", *(token[2].size));
	while (i < size)
	{
		printf("Token(%d)\n", i);
		print_token(&token[i]);
		i++;
	}
}