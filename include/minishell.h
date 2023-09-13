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
# include "tokens.h"

typedef struct s_environment
{
	char					*key;
	char					*value;
	struct s_environment	*next;
}	t_env;

typedef struct s_shell
{
	char	*last_command;
	t_list	*parsed_tokens;
	t_list	*environment;
}	t_shell;

typedef struct s_info
{
	char			**command;
	t_list			*inf;
	t_list			*outf;
	int				fd_in;
	int				fd_out;
	struct s_info	*next;
	struct s_info	*prev;
}	t_info;

typedef	struct s_file_node
{
	char 		*file_name;
	t_tag 		type;
}	t_file_node;

//typedef struct s_readline
//{
//	char			**command;
//	char			*heredoc;
//	char			**append_out_file;
//	char			**redirect_out_file;
//	char			**redirect_in_file;
//	t_tag			tag;
//}	t_readline;

//Typedefs

int		add_environment_variable(t_env **env, char *key, char *value);
int		get_environment_size(t_env **env);
t_env	*find_environment_key(t_env **env, char *key);
char	**find_environment_key_as_2d(t_env **env, char *key);

t_info	*ms_readline(t_shell *shell, char *str);
void	exec_loop(t_info *info, char *envp[]);

#endif
