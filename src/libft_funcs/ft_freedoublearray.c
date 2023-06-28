/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_freedoublearray.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cbijman <cbijman@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 15:13:52 by cbijman       #+#    #+#                 */
/*   Updated: 2023/06/28 15:22:03 by mvalk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_double_array(char **s)
{
	u_int32_t	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}
