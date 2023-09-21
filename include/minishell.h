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
# include <unistd.h>
# include <sys/types.h>
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

# ifdef HISTORY_FILE
#  undef HISTORY_FILE
# endif

# define PREFIX "\x1B[1;32m>> \x1B[0m"
# define HISTORY_FILE ".minishell_history"
# define MAX_BUILTIN 10

typedef struct s_shell	t_shell;

typedef int				(*t_builtin_func)(t_shell *, int, char **);

typedef struct s_builtin
{
	char			*command;
	t_builtin_func	__builtin_handler;
}	t_builtin;

typedef struct s_environment
{
	char					*key;
	char					*value;
	struct s_environment	*next;
}	t_env;

typedef struct s_shell
{
	int			exited;
	char		*last_command;
	t_builtin	*(builtins[MAX_BUILTIN]);
	size_t		size;
	t_list		*parsed_tokens;
	t_env		**environment;
	char		**envp;
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

t_info	*ms_readline(t_shell *shell);
void	register_signals();
void	exec_loop(t_shell *shell, t_info *info, char *envp[]);


//History
int		open_historyfile(void);
void	ms_add_history(char	*str);

//Builtins
int		get_builtin_size(t_shell *shell);
bool	does_builtin_exist(t_shell *shell, char *command);
bool	set_builtin(t_shell *shell, char *command, t_builtin_func func);
bool	fire_builtin(t_shell *shell, char **argv);
void	free_builtin(t_builtin *in);
void	print_builtins(t_shell *shell);

//Builtin functions
int		ft_cd(t_shell *shell, int ac, char **av);
int		ft_unset(t_shell *shell, int ac, char **av);
int		ft_export(t_shell *shell, int ac, char **av);
int		ft_env(t_shell *shell, int ac, char **av);
int		ft_pwd(t_shell *shell, int ac, char **av);
int		ft_exit(t_shell *shell, int ac, char **av);
int		ft_echo(t_shell *shell, int ac, char **av);

//Signals
void	handle_control_d(t_shell *shell);

//Test
char	*find_expansion(t_env **env, const char *key);
bool	add_expansion(t_env **env, char *key, char *value);

#endif
