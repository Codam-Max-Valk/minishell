/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_space.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvalk <mvalk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 15:29:40 by mvalk         #+#    #+#                 */
/*   Updated: 2023/06/29 15:46:35 by mvalk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_substrlen(char const *s)
{
	size_t	substr_len;

	substr_len = 0;
	while (s[substr_len] != '\0' && !ft_isspace(s[substr_len]))
		substr_len++;
	return (substr_len);
}

static	size_t	ft_strcounter(char const *s)
{
	size_t	str_count;
	size_t	index;

	str_count = 0;
	index = 0;
	while (index < ft_strlen(s))
	{
		if (!ft_isspace(s[index]))
		{
			index = index + ft_substrlen(&s[index]);
			str_count++;
		}
		index++;
	}
	return (str_count + 1);
}

static	int	ft_free_split_str(char **split_str, ssize_t array_i)
{
	if (!split_str[array_i])
	{
		while (array_i >= 0)
		{
			free (split_str[array_i]);
			array_i--;
		}
		free (split_str);
		return (0);
	}
	return (1);
}

char	**ft_split_space(char const *s)
{
	ssize_t	array_i;
	char	**split_str;

	array_i = 0;
	if (!s)
		return (0);
	split_str = (char **)malloc(sizeof(char *) * ft_strcounter(s));
	if (!split_str)
		return (0);
	while (*s != '\0')
	{
		if (!ft_isspace(*s))
		{
			split_str[array_i] = ft_substr((char *)s, 0, ft_substrlen(s));
			if (!(ft_free_split_str(split_str, array_i)))
				return (NULL);
			s = s + ft_substrlen(s);
			array_i++;
		}
		else
			s++;
	}
	split_str[array_i] = NULL;
	return (split_str);
}

// int main(void)
// {
// 	char *a = "      split       this for   me  !";
// 	size_t	i = 0;
// 	char	**split_a = ft_split(a, ' ');

// 	printf("stringcount: %lu\n", ft_strcounter(a, ' '));
// 	while (i < ft_strcounter(a, ' '))
// 	{
// 		printf("string %lu: %s\n", i, split_a[i]);
// 		i++;
// 	}
// 	for(int i = 0; split_a[i] != NULL; i++)
// 		free(split_a[i]);
// 	free (split_a);
// 	system("leaks -q a.out");
// 	return (0);
// }
