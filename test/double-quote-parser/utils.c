#include "shell.h"

const char	*ft_readline(void)
{
	const char  *str = readline(PREFIX);

	if (!str)
		return (printf("exit\n"), exit(1), NULL);
	return (str);
}

const char	*get_tag_name(t_tag tag)
{
	const	char *(tag_table[100]) = {\
		[T_DOUBLE_QUOTE] = "Double Quote", \
		[T_SINGLE_QUOTE] = "Single Quote", \
		[T_REDIRECT_IN] = "Redirect In", \
		[T_REDIRECT_OUT] = "Redirect Out", \
		[T_PIPE] = "Pipe", \
		[T_APPEND] = "Append", \
		[T_HERE_DOC] = "Heredoc", \
		[T_EQUALS] = "Equals", \
		[T_EXPANSION] = "Expansions", \
		[T_SEMICOLUMN] = "Semi column", \
		[T_COMMAND] = "Command/Argument", \
		[T_NONE] = "None", \
	};

	if (!tag_table[tag])
		return ("Unrecognized token");
	return (tag_table[tag]);
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
		printf("Token (%zu)\n", i);
		printf("%8s-> Content: %s\n", BOLD_GREEN, token->content);
		printf("%8s-> Length: %d\n", BOLD_GREEN, token->length);
		printf("%8s-> Tag: %s\n", BOLD_GREEN, get_tag_name(token->tag));
		printf(RESET);
		i++;
		tmp = tmp->next;
	}
}
