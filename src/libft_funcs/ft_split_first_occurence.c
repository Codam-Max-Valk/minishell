/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_first_occurence.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cbijman <cbijman@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/29 17:30:43 by cbijman       #+#    #+#                 */
/*   Updated: 2023/09/18 17:44:06 by mvalk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_split_first_occurrence(char *line, char delimiter)
{
	size_t	i;
	char	**s;

	s = malloc(sizeof(char *) * 3);
	if (!s)
		return (NULL);
	i = 0;
	while (line[i] != delimiter)
		i++;
	s[0] = ft_substr(line, 0, i++);
	if (ft_isnull(s[0]))
		return (free(s), NULL);
	s[1] = ft_strdup(&line[i]);
	if (ft_isnull(s[1]))
		return (free(s[0]), free(s), NULL);
	s[2] = NULL;
	return (s);
}
