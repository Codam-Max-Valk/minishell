/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isspace.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yfu <marvin@42.fr>                           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 15:59:59 by yfu           #+#    #+#                 */
/*   Updated: 2023/09/26 18:58:38 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}
