#include "include/shell.h"

t_token	*ft_tokennew(const char *content, t_tag tag)
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

bool	ft_token_addback(t_list **lst, const char *str, t_tag tag)
{
	t_list	*tmp;
	t_token	*token;

	token = ft_tokennew(str, tag);
	tmp = ft_lstnew(token);
	ft_lstadd_back(lst, tmp);
	return (true);
}

char	*find_envp(char *key, char **envp)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(key);
	while (envp[i] && strncmp(key, envp[i], len))
		i++;
	if (!envp[i])
		return (NULL);
	return (envp[i] + (len + 1));
}

char	*find_envpl(const char *key, char **envp, int len)
{
	size_t	i;

	i = 0;
	while (envp[i] && strncmp(key, envp[i], len))
		i++;
	if (!envp[i])
		return (NULL);
	return (envp[i] + (len + 1));
}

int	get_expansion_length(const char *str)
{
	int	i;

	if (str[0] != '$')
		return (PARSE_FAILURE);
	i = 1;
	if (ft_isdigit(str[i]))
	{
		while (ft_isdigit(str[i]))
			i++;
		return (i = -i);
	}
	if (!ft_isalnum(str[1]))
		return (PARSE_FAILURE);
	while (str[i] && ft_isalnum(str[i]))
		i++;
	return (i);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
			printf("Expansion length: %zu, String: %s\n", j, ft_substr(str, i, j));
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

int	tokenize_quote(t_list **lst, const char *str, char **envp)
{
	char	type;
	char	*nstr;
	size_t	i;

	type = *str;
	i = 1;
	while (str[i] && str[i] != type)
		i++;
	if (str[i++] != type)
		return (printf("error: Unclosed quotes\n"), i);
	nstr = ft_substr(str, 0, i);
	if (!nstr)
		return (printf("error"), i);
	if (type == '\"')
	{
		nstr = handle_double_quote(nstr, envp);
		if (!nstr)
			return (i /* Add more error control... */);
		ft_token_addback(lst, nstr, T_DOUBLE_QUOTE);
		return (i);
	}
	ft_token_addback(lst, nstr, T_SINGLE_QUOTE);
	return (i);
}

int	tokenize_expansion(t_list **lst, const char *str, char **envp)
{
	char	*nstr;
	int		len;

	len = 0;
	if (str[len] != '$')
		return (PARSE_FAILURE);
	len = get_expansion_length(str);
	if (len <= PARSE_FAILURE)
		return (-len + 1);
	nstr = find_envpl(str + 1, envp, len - 1);
	if (!nstr)
		ft_token_addback(lst, "\0", T_EXPANSION);
	else
		ft_token_addback(lst, nstr, T_EXPANSION);
	return (len);
}

int	tokenize_content(t_list **lst, const char *str)
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
		return (PARSE_FAILURE);
	ft_token_addback(lst, nstr, T_COMMAND);
	return (len);
}

int	tokenize_redirect(t_list **lst, const char *str)
{
	char	*nstr;
	int		i;
	int		oldi;
	int		len;

	i = 1;
	len = 0;
	if (str[i] == '>' || str[i] == '<')
		i++;
	while (str[i] && ft_isspace(str[i]) && str[i] != '>' && str[i] != '<')
		i++;
	if (!ft_isprint(str[i]) && (str[i] == '>' || str[i] == '<'))
		return (PARSE_FAILURE);
	oldi = i;
	while (str[i] && ft_isprint(str[i])
		&& str[i] != '>' && str[i] != '<' && str[i] != '|' && str[i] != ' ')
	{
		i++;
		len++;
	}
	nstr = ft_substr(str, oldi, len);
	if (!nstr)
		return (-1);
	ft_token_addback(lst, nstr, T_REDIRECT_IN);
	return (oldi + len); //echo $USER > out | cat -e < infile cat | ls
}

int	tokenize_pipe(t_list **list)
{
	ft_token_addback(list, "|", T_PIPE);
	return (1);
}

t_list	*parse(const char *s, char **envp)
{
	t_list	*lst;
	size_t	i;

	lst = NULL;
	i = 0;
	while (s[i])
	{
		if (ft_isspace(s[i]))
			i += 1;
		else if (s[i] == '\"' || s[i] == '\'')
			i += tokenize_quote(&lst, &s[i], envp);
		else if (s[i] == '$')
			i += tokenize_expansion(&lst, &s[i], envp);
		else if (s[i] == '|')
			i += tokenize_pipe(&lst);
		else if (s[i] == '>' || s[i] == '<')
			i += tokenize_redirect(&lst, &s[i]);
		else
			i += tokenize_content(&lst, &s[i]);
	}
	return (lst);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int	ft_isquote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

char	*insert_string(char *s1, char *s2, int i)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1, i + 1);
	ft_strlcpy(&new_str[i], s2, len2 + 1);
	ft_strlcpy(&new_str[len1 + len2 - i], &s1[i], ft_strlen(&s1[i]) + 1);
	return (new_str);
}

char	*handle_expansion_raw(char *s, char **envp)
{
	size_t	j;
	size_t	k;
	size_t	len;
	char	*expander;
	char	*variable;


	//Checkers
	size_t	i;
	int		in_dq;
	int		in_sq;
	char	*nstr;

	nstr = ft_calloc(128 * 8, 1);
	in_sq = 0;
	in_dq = 0;
	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			j = i;
			len = 0;
			while (ft_isprint(s[j]) && !ft_isspace(s[j]) && !ft_isquote(s[j]))
			{
				j++;
				len++;
			}
			expander = ft_substr(s, i, len);
			variable = find_envp(&expander[1], envp);
			if (!variable)
			{
				nstr[i] = 32;
				i++;
				j++;
				continue ;
			}
			printf("Expander is %s (%s)\n", expander, variable);

			//We have to append the environment variable here to the new string and update both indexes from both strings to they stay synchronized...
			ft_strcpy(&nstr[i], variable);
			i += (len);
			j += (ft_strlen(variable));
			//nstr = ft_strjoin_free(nstr, &s[i]);
			printf("New string: %s\n", nstr);
		}
		i++;
		j++;
		nstr[j] = s[i];
	}

	return (nstr);
}

int main(int ac, char **av, char **envp)
{
	t_list	*lst;
	char	*str;

	str = "\"$LOGNAME\" \"$USER \'$PWD\'\" \'$CWD \"$SHLVL\"\' $PATH";
	printf(GREEN);
	printf("Before: %s\n", str);
	printf("Afterr: %s\n", handle_expansion_raw(str, envp));
	printf(RESET);

	//while (true)
	//{
	//	str = ft_readline();
	//	lst = parse(str, envp);
	//	print_tokens(lst);
	//}

	return (0);
}

