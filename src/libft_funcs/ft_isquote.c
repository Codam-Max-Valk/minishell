/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isquote.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cbijman <cbijman@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 17:18:03 by cbijman       #+#    #+#                 */
/*   Updated: 2023/07/12 13:22:40 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_issemiquote(char c)
{
	if (c == '\'')
		return (1);
	return (0);
}

int	ft_isdoublequote(char c)
{
	if (c == '\"')
		return (1);
	return (0);
}

int	ft_isquote(char c)
{
	if (ft_issemiquote(c) || ft_isdoublequote(c))
		return (1);
	return (0);
}
