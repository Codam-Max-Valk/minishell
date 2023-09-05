/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cbijman <cbijman@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 16:53:18 by cbijman       #+#    #+#                 */
/*   Updated: 2023/09/05 15:29:57 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H
# include <stdbool.h>
# include <stdio.h>

# define DELIM "><| \t\n\v\f\r"

# define PIPE "|"
# define DOUBLE_QUOTE "\""
# define SINGLE_QUOTE "\'"
# define REDIRECT_IN "<"
# define REDIRECT_OUT ">"
# define APPEND ">>"
# define HERE_DOC "<<"
# define ARGUMENT "-"

typedef enum e_tag
{
	T_DOUBLE_QUOTE = 1,
	T_SINGLE_QUOTE = 2,
	T_REDIRECT_IN = 3,
	T_REDIRECT_OUT = 4,
	T_PIPE_ICON = 5,
	T_APPEND = 6,
	T_HERE_DOC = 7,
	T_COMMAND = 8,
	T_ARGUMENT = 9,
}	t_tag;

typedef struct s_token
{
	char			*content;
	t_tag			tag;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_zoekjijmaaruitmax
{
	char			**command;
	char			*heredoc;
	char			**append_out_file;
	char			**redirect_out_file;
	char			**redirect_in_file; //[norminette] | [(grep -v "OK") > (out)] && [cat (out)] | [(grep -v "Error") (> out2 > out3)]
	t_tag			tag;
	struct s_token	*next;
	struct s_token	*prev;
}	t_zoekjijmaaruitmax;

//Checkers
int		tag_isquote(t_tag tag);
t_tag	guess_tag(char *s);
int		get_token_length(t_tag tag);

#endif