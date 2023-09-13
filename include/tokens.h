/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cbijman <cbijman@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 16:53:18 by cbijman       #+#    #+#                 */
/*   Updated: 2023/09/13 14:45:19 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H
# include <stdbool.h>
# include <stdio.h>

# define DELIMITOR "><\"\' \t\n\v\f\r"

# define PIPE "|"
# define EQUALS "="
# define EXPANSION "$"
# define SEMICOLUMN ";"
# define DOUBLE_QUOTE "\""
# define SINGLE_QUOTE "\'"
# define REDIRECT_IN "<"
# define REDIRECT_OUT ">"
# define APPEND ">>"
# define HERE_DOC "<<"

# define PARSE_FAILURE -1

typedef enum e_tag
{
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
	T_COMMAND		= 11,
	T_ARGUMENT		= 12,
	T_END			= 13,
}	t_tag;

typedef struct s_token
{
	char			*content;
	t_tag			tag;
	struct s_token	*next;
}	t_token;

//Typedefs for function pointers.
typedef int		(*t_token_lengthfunc)(char *);
typedef void	(*t_token_clearfunc)(t_token *);

//lexer_lst.c
t_token		*create_token(char *arg, t_tag tag);
void		token_addback(t_token **tokens, t_token *token);
size_t		token_lstsize(t_token *token);
void		token_lstclear(t_token **tokens, t_token_clearfunc func);
void		token_free(t_token *token);

//lexer_helpers.c
t_tag		guess_tag(char *s);
int			ft_istoken(char *s);
int			ft_issymbol(t_tag tag);

//lexer_utils.c * TODO: Add string checks.
int			get_quote_length(char *s);
int			get_symbol_length(char *s);
int			get_content_length(char *s);
int			get_redirect_length(char *s);
int			get_token_length(t_tag tag);

//lexer.c
t_token		*tokenizer2(char *s);

//Remove once done.
const char	*get_tag_name(t_tag tag);

#endif