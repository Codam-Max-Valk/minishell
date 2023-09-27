/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_safe_strdup.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cbijman <cbijman@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 13:56:23 by cbijman       #+#    #+#                 */
/*   Updated: 2023/09/27 13:56:38 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_safe_strdup(const char *s1)
{
	int		len;
	char	*str;

	if (!s1)
		len = 1;
	else
		len = (ft_strlen(s1) + 1);
	str = (char *)malloc(len * sizeof(char));
	if (str == 0)
		return (0);
	if (!s1)
		ft_strlcpy(str, "\0", len);
	else
		ft_strlcpy(str, (char *)s1, len);
	return (str);
}