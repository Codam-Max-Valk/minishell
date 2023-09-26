/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_freedoublearray.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cbijman <cbijman@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 15:13:52 by cbijman       #+#    #+#                 */
/*   Updated: 2023/09/26 18:58:24 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include <stdlib.h>

void	free_double_array(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i])
			free(s[i]);
		i++;
	}
	free(s);
}
