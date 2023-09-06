/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cbijman <cbijman@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 16:53:18 by cbijman       #+#    #+#                 */
/*   Updated: 2023/09/06 17:08:10 by cbijman       ########   odam.nl         */
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

# define PARSE_FAILURE -1

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
	char			**redirect_in_file;
	t_tag			tag;
	struct s_token	*next;
	struct s_token	*prev;
}	t_zoekjijmaaruitmax;

//TODO : Dit gaat nog veranderd worden qua indeling en benamingen.
typedef int (*t_lengthfunc)(char *);
typedef void (*t_token_clear_func)(t_token *);

//lexer_lst.c
t_token	*create_token(char *arg, t_tag tag);
void	token_addback(t_token **tokens, t_token *token);
size_t	token_lstsize(t_token *token);
void	token_lstclear(t_token **tokens, t_token_clear_func func);
void	token_free(t_token *token);

//lexer_helpers.c
int		get_token_length(t_tag tag);
t_tag	guess_tag(char *s);
int		ft_istoken(char *s);

//lexer_utils.c * TODO: Add string checks.
int	get_quote_length(char *s);
int	get_symbol_length(char *s);
int	get_content_length(char *s);

//lexer.c
t_token	*tokenizer2(char *s);



#endif