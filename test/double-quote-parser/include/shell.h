#ifndef SHELL_H
# define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#include <readline/readline.h>

#include "libft.h"
#include "colors.h"

#define PREFIX "Hella Cash >> "
#define PARSE_FAILURE -1

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
	int		length;
	t_tag	tag;
}	t_token;

const char	*ft_readline(void);
void		print_tokens(t_list *lst);

#endif