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

# ifdef MAX_BUILTIN
#  undef MAX_BUILTIN
# endif

# define MAX_BUILTIN 10
typedef struct s_shell t_shell;

typedef int	(*t_builtin_func)(t_shell *, int, char **);

typedef struct s_builtin
{
	char	*command;
	int		(*__builtin_handler)(t_shell *, int, char **);
}	t_builtin;

typedef struct s_environment
{
	char					*key;
	char					*value;
	struct s_environment	*next;
}	t_env;

typedef struct s_shell
{
	char		*last_command;
	t_builtin	*(builtins[10]);
	size_t		size;
	t_list		*parsed_tokens;
	t_list		*environment;
}	t_shell;

typedef struct s_info
{
	char			**command;
	t_token			*inf;
	t_token			*outf;
	int				pipe_fd[2];
	int				fd_in;
	int				fd_out;
	struct s_info	*next;
	struct s_info	*prev;
}	t_info;

int		add_environment_variable(t_env **env, char *key, char *value);
int		get_environment_size(t_env **env);
t_env	*find_environment_key(t_env **env, char *key);
char	**find_environment_key_as_2d(t_env **env, char *key);

t_info	*ms_readline(t_shell *shell, char *str);
void	exec_loop(t_info *info, char *envp[]);


//Builtins
int		get_builtin_size(t_shell *shell);
bool	does_builtin_exist(t_shell *shell, char *command);
bool	set_builtin(t_shell *shell, char *command, t_builtin_func func);
bool	fire_builtin(t_shell *shell, char **argv);
void	free_builtin(t_builtin *in);
void	print_builtins(t_shell *shell);

//Builtin functions
int		ft_cd(t_shell *shell, int argc, char **argv);

#endif
