/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   testshell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cbijman <cbijman@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 14:46:42 by cbijman       #+#    #+#                 */
/*   Updated: 2023/11/22 15:14:04 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTSHELL_H
# define TESTSHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <readline/readline.h>

# include "libft.h"

# define PREFIX "MeesGang >> "

typedef	struct s_testshell
{
	char	**envp;
}	t_testshell;

typedef enum e_tag
{
	T_NONE			= 0,
	T_DOUBLE_QUOTE	= 1,
	T_SINGLE_QUOTE	= 2,
	T_REDIRECT_IN	= 3,
	T_REDIRECT_OUT	= 4,
	T_PIPE			= 5,
	T_APPEND		= 6,
	T_HERE_DOC		= 7,
	T_EQUALS		= 8,
	T_EXPANSION		= 9,
	T_SEMICOLUMN	= 10,
	T_COMMAND		= 11
}	t_tag;

typedef struct s_token
{
	char	*content;
	int		*size;
	int		type;
}	t_token;

char	*ft_readline(void);
void	print_token_list(t_token *token);


#endif