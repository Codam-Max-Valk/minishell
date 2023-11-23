#include "testshell.h"
#include "colors.h"

///////////////////////////////// * Environmental Methods * //////////////////////////////////////////////////////////////////

void	env_init(t_testshell *shell, char **envp)
{
	shell->envp = envp;
}

///////////////////////////////// * Quote Handling * //////////////////////////////////////////////////////////////////////////

char *find_env(char *key, char **cmp)
{
	while (ft_strncmp(key, (*cmp), ft_strlen(key)))
		cmp++;
	return (*cmp);
}

char *parse_quote(char **envp, char *str)
{

}

t_token	new_token(char *str, t_tag type, int *size)
{
	t_token token;

	ft_bzero(&token, sizeof(t_token));
	token.content = ft_strdup(str);
	token.type = (int) type;
	token.size = size;
	return (token);
}

///////////////////////////////// * Parse Methods * //////////////////////////////////////////////////////////////////////////

int	add_trash(t_token *token, int *size, char *str)
{
	if (*str != '|')
		return (1);
	token[(*size)++] = new_token("|", T_PIPE, size);
	return (1);
}

int	add_expansion_token(t_token *token, int *size, char *str)
{
	char	*nstr;
	int		len;

	len = 0;
	if (str[len] != '$')
		return (-1);
	len++;
	while (ft_isalnum(str[len]))
		len++;
	nstr = ft_substr(str, 0, len);
	if (!nstr)
		return (-1);
	token[(*size)++] = new_token(nstr, T_EXPANSION, size);
	return (len);
}

int	add_command_token(t_token *token, int *size, char *str)
{
	char	*nstr;
	int		len;

	len = 0;
	while (str[len]
		&& str[len] != '|' 
		&& str[len] != '<' 
		&& str[len] != '>' 
		&& !ft_isspace(str[len]))
		len++;
	nstr = ft_substr(str, 0, len);
	if (!nstr)
		return (-1);
	token[(*size)++] = new_token(nstr, T_COMMAND, size);
	return (len);
}

int	add_redirect_token(t_token *token, int *size, char *str)
{
	char	*nstr;
	int		len;

	len = 0;
	while (str[len] && (str[len] == '<' || str[len] == '>'))
		len++;
	nstr = ft_substr(str, 0, len);
	if (!nstr)
		return (-1);
	token[(*size)++] = new_token(nstr, T_REDIRECT_IN, size);
	return (len);
}

int	add_quote_token(t_testshell *shell, t_token *token, int *size, char *str)
{
	char	*nstr;
	int		len;

	len = 0;
	while (str[len] && str[len] != *str)
		len++;
	nstr = ft_substr(str, 0, len);
	if (!nstr)
		return (-1);
	if (*str == '\"')
		token[(*size)++] = new_token(nstr, T_DOUBLE_QUOTE, size);
	else if (*str == '\'')
		token[(*size)++] = new_token(nstr, T_SINGLE_QUOTE, size);
	return (len);
}

/**
 * @brief Parse the command line,
 * 
 * @param shell 
 * @param str Example: echo "$USER '$USER'" '$USER' | cat -e // Output should be "cbijman 'cbijman'" '$USER'
 * @return t_token* 
 */
t_token	*parse(t_testshell *shell, char	*str)
{
	t_token	*lst;
	int		i;
	int		x;
	int		length;
	int		elements;
		
	lst = (t_token *) ft_calloc(16 /* Calculate the string. */, sizeof(t_token));
	i = 0;
	x = 0;
	elements = 0;
	length = ft_strlen(str);
	while (str[i])
	{
		if (ft_isspace(str[i]))
			i++;
		else
		{
			if (str[i] == '|')
				x = add_trash(lst, &elements, &str[i]);
			else if (str[i] == '$')
				x = add_expansion_token(lst, &elements, &str[i]);
			else if (str[i] == '<' || str[i] == '>')
				x = add_redirect_token(lst, &elements, &str[i]);
			else if (str[i] == '\"' || str[i] == '\'')
				x = add_quote_token(shell, lst, &elements, &str[i]);
			else
				x = add_command_token(lst, &elements, &str[i]);
			printf("(%d/%d) %s\n", i, length, &str[i]);
			i += (x - 1);
		}
		i++;
	}
	return (lst);
}

///////////////////////////////// * Main Methods * //////////////////////////////////////////////////////////////////////////

char	*ft_readline(void)
{
	char *str;

	str = readline(PREFIX);
	if (!str)
		return (printf("exit\n"), exit(0), NULL);
	add_history(str);
	return (str);
}

int main(int ac, char **av, char **envp)
{
	t_testshell shell;
	size_t		index;
	t_token		*tokens;


	ft_bzero(&shell, sizeof(t_testshell));
	env_init(&shell, envp);
	tokens = NULL;
	index = 0;
	while (envp[index])
	{
		printf("[%sTestshell%s] %s\n", BOLD_RED, RESET, envp[index]);
		index++;
	}
	printf("[%sFind Comparison%s] Found path: %s\n", BOLD_MAGENTA, RESET, find_env("PATH", envp));
	while (true)
	{
		tokens = parse(&shell, ft_readline());
		if (!tokens)
			continue;
		print_token_list(tokens);
	}
}