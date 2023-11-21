#include "testshell.h"

typedef struct s_token
{
	char	*content;
	int		type;
	int		*size;
	struct s_token *token;
}	t_token;


///////////////////////////////// * Environmental Methods * //////////////////////////////////////////////////////////////////

void	env_init(t_testshell *shell, char **envp)
{

}

///////////////////////////////// * Parse Methods * //////////////////////////////////////////////////////////////////////////

t_token	new_token(char *str, int type, int size)
{
	t_token token;

	ft_bzero(&token, sizeof(t_token));
	token.content = ft_strdup(str);
	token.type = type;
	token.size = &size;
	return (token);
}

/**
 * @brief Parse the command line,
 * 
 * @param shell 
 * @param str Example: echo "$USER '$USER'" '$USER' | cat -e // Output should be 'cbijman 'cbijman' $USER'
 * @return t_token* 
 */
t_token	*parse(t_testshell *shell, char	*str)
{
	t_token	*lst;
	size_t	index;
		
	lst = (t_token *) ft_calloc(10, sizeof(t_token));
	index = 0;
	lst[index++] = new_token("echo", 4, index); //Command
	lst[index++] = new_token("\"$USER \'$USER\'\" \'$USER\'", 5, index); //Double quote with expansion
	lst[index++] = new_token("|", 3, index); //Pipe
	lst[index++] = new_token("cat", 4, index); //Command
	lst[index++] = new_token("-e", 5, index); //Argument
	return (lst);
}

///////////////////////////////// * Main Methods * //////////////////////////////////////////////////////////////////////////

char	*ft_readline(void)
{
	char *str;

	str = readline(PREFIX);
	if (!str)
		return (printf("exit\n"), exit(0), NULL);
	return (str);
}

void	print_token_list(t_token *token)
{
	int	i;
	
	i = 0;
	printf("Token list size: %d\n", *(token[2].size));
	while (i < *(token[2].size))
	{
		printf("Token Type: %d\n", token->type);
		i++;
	}
}

int main(int ac, char **av, char **envp)
{
	t_testshell shell;

	ft_bzero(&shell, sizeof(t_testshell));

	env_init(&shell, envp);
	while (true)
	{
		t_token *tokens;
		tokens = parse(&shell, ft_readline());
		print_token_list(tokens);
	}
}