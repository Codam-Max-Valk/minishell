/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cbijman <cbijman@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 16:53:18 by cbijman       #+#    #+#                 */
/*   Updated: 2023/07/13 16:55:50 by cbijman       ########   odam.nl         */
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
	double_quote = 1,
	single_quote = 2,
	redirect_in = 3,
	redirect_out = 4,
	pipe_icon = 5,
	append = 6,
	here_doc = 7,
	argument = 8,
}	t_tag;

typedef struct s_token
{
	char			*content;
	t_tag			tag;
	bool			is_token;
	bool			is_command;
	char			*redirect_out_file;
	char			*redirect_in_file;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_token
{
	char			**command;
	char			*heredoc;
	char			**append_out_file;
	char			**redirect_out_file;
	char			**redirect_in_file; //[norminette] | [(grep -v "OK") > (out)] && [cat (out)] | [(grep -v "Error") (> out2 > out3)]
	t_tag			tag;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

//Checkers
int		tag_isquote(t_tag tag);
t_tag	guess_tag(char *s);
int		get_token_length(t_tag tag);

#endif