
#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <signal.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "colors.h"

typedef struct s_env_key
{
	char	*key;
	char	*value;
}	t_env_key;

typedef	struct s_tokens
{
	char	**split_input;
	char	*command;
	char	**arguments;
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

t_list		*setup_environment(char **envp);
t_env_key	*find_environment_key(t_list **env, char *key);
void		free_envkey(t_env_key *ek);

#endif
