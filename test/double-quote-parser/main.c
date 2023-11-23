#include "shell.h"

t_token	*ft_tokennew(char *content, t_tag tag)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = ft_strdup(content);
	token->length = ft_strlen(content);
	token->tag = tag;
	return (token);
}

bool	ft_token_addback(t_list **lst, char *str, t_tag tag)
{
	t_list	*tmp;
	t_token	*token;

	token = ft_tokennew(str, tag);
	tmp = ft_lstnew(token);
	ft_lstadd_back(lst, tmp);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char	*find_envp(char *key, char **envp)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(key);
	while (envp[i] && strncmp(key, envp[i], len))
		i++;
	return (envp[i] + (len + 1));
}

int	get_expansion_length(char *str)
{
	int	i;

	if (str[0] != '$')
		return (0);
	i = 1;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	return (i);
}

char	*handle_double_quote(char *str, char **envp)
{
	size_t	i;
	size_t	j;
	char	*nstr;
	char	*expansion;

	i = 0;
	j = 0;
	nstr = ft_calloc(128, 1);
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = get_expansion_length(&str[i]);
			printf("Expansion length: %d, String: %s\n", j, ft_substr(str, i, j));
			nstr = ft_strjoin(nstr, find_envp("USER", envp));
			if (!nstr)
				return (NULL);
			i += j;
		}
		else
			nstr[j++] = str[i];
		i++;
	}
	return (nstr);
}

//echo "$USER user '$USER'" '$user'

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int	tokenize_quote(t_list **lst, const char *str, char **envp)
{
	char	type;
	char	*nstr;
	size_t	i;

	type = *str;
	i = 1;
	while (str[i] && str[i] != type)
	{
		i++;
	}
	if (str[i++] != type)
	{
		return (printf("error: Unclosed quotes\n"), i);
	}
	nstr = ft_substr(str, 0, i);		
	if (type == '\"')
	{
		nstr = handle_double_quote(nstr, envp);
		if (!nstr)
			return (i /* Add more error control... */);
		ft_token_addback(lst, nstr, T_DOUBLE_QUOTE);
		return (i);
	}
	else
	{
		ft_token_addback(lst, nstr, T_SINGLE_QUOTE);
		return (i);
	}
	return (i);
}

t_list	*parse(const char *s, char **envp)
{
	t_list	*lst;
	size_t	i;

	lst = NULL;
	i = 0;
	while (s[i])
	{
		if (ft_strchr("<>\"\'|$", s[i]))
		{
			if (s[i] == '\"' || s[i] == '\'')
				i += tokenize_quote(&lst, &s[i], envp);
		}
		i++;
	}
	return (lst);
}

int main(int ac, char **av, char **envp)
{
	t_list  *lst;
	t_list  *tmp;

	lst = parse("echo \"$USER user \'$USER\'\" '$USER'", envp);
	print_tokens(lst);

	return (1);
}

