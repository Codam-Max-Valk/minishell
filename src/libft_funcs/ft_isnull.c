/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isnull.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cbijman <cbijman@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 13:33:24 by cbijman       #+#    #+#                 */
/*   Updated: 2023/09/27 12:18:19 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int32_t	ft_isnull(char *s)
{
	if (!s || !*s)
		return (1);
	return (0);
}
