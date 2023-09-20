/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvalk <mvalk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 17:13:23 by mvalk         #+#    #+#                 */
/*   Updated: 2023/09/20 17:13:24 by mvalk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/libft.h"

int	ft_exit(t_shell *shell, int argc, char **argv)
{
	return (shell->exited = 0);
}
