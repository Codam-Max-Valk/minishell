#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdbool.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "colors.h"

typedef enum e_tag
{
	file,
	command,
	argument,
	redirect_in,
	redirect_out,
	append,
	here_doc,
	pipe
}	t_tag;

typedef struct s_token
{
	char	*token;
	t_tag	tag;
}	t_token;

typedef struct s_environment
{
	char					*key;
	char					*value;
	struct s_environment	*next;
}	t_env;

typedef struct s_tokens
{
	char	**split_input;
	t_token	**redirect;
	t_token	**commands;
	bool	redirect_in;
	bool	redirect_out;
	bool	append;
	bool	here_doc;
	bool	pipe;
}	t_tokens;

typedef struct s_shell
{
	char	*last_read_line;
	t_list	*environment;
}	t_shell;

int		add_environment_variable(t_env **env, char *key, char *value);
int		get_environment_size(t_env **env);
t_env	*find_environment_key(t_env **env, char *key);
char	**find_environment_key_as_2d(t_env **env, char *key);

#endif
