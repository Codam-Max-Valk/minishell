/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cbijman <cbijman@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 16:53:18 by cbijman       #+#    #+#                 */
/*   Updated: 2023/07/11 17:57:17 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H
# include <stdbool.h>
# define DELIM "><| \t\n\v\f\r"

# define PIPE "|"
# define DOUBLE_QUOTE "\""
# define SINGLE_QUOTE "\'"
# define REDIRECT_IN "<"
# define REDIRECT_OUT ">"
# define APPEND ">>"
# define ARGUMENT "-"
# define HERE_DOC "<<"

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
	t_tag			tag;
	bool			is_token;
	bool			is_command;
	char			*content;
	void			*command;
	char 			**redir_in;
	char 			**redir_out;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

void	*create_token(char *token, t_tag tag);

//Checkers
int	tag_isquote(t_tag tag);

#endif