#include "../include/minishell.h"

int	main(void)
{
	char *str;

	while (1)
	{
		str = readline("Minishell >> ");
		printf("%s\n", str);
		free(str);
	}
}
