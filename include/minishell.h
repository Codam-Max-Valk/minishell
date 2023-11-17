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

# define DEBUG 1

typedef struct s_shell	t_shell;

typedef int				(*t_builtin_func)(t_shell *, int, char **);

typedef enum e_envtype
{
	ENVIRONMENT,
	LOCAL_ENVIRONMENT,
	NONE
}	t_envtype;

typedef struct s_builtin
{
	char			*command;
	t_builtin_func	__builtin_handler;
}	t_builtin;

typedef struct s_environment
{
	char					*key;
	char					*value;
	t_envtype				type;
	struct s_environment	*next;
}	t_env;

typedef struct s_shell
{
	int			stdin_fd;
	int			stdout_fd;
	int			pipe_fd[2];
	int			exited;
	int			exit_code;
	char		*last_command;
	t_builtin	*(builtins[MAX_BUILTIN]);
	size_t		size;
	t_list		*parsed_tokens;
	char		**envp;
	t_env		*environment;
	t_env		*expansion;
}	t_shell;

typedef struct s_info
{
	pid_t			pid;
	char			**command;
	t_token			*inf;
	t_token			*outf;
	int				pipe_in;
	int				pipe_out;
	int				pipe_fd[2];
	int				fd_in;
	int				fd_out;
	bool			is_builtin;
	struct s_info	*next;
}	t_info;

typedef	enum	e_io
{
	input,
	output
}	t_io;

//String
char	*ft_replaceall(const char *str, char c);

//Parser
t_info	*parse_tokens(t_shell *shell, t_token **tokens);
t_info	*ms_readline(t_shell *shell);
void	register_signals(void);

//Executor
void	reset_fd(t_shell *shell);
char	**parse_env(char **envp);
char	*cmd_path(char **paths, char *cmd, int path_f);
void	exec_loop(t_shell *shell, t_info **info, char **env);
void	set_redir_out(t_shell *shell, t_info *info, t_token *file);
void	set_redir_in(t_shell *shell, t_info *info, t_token *file);
void	reset_info_fd(t_info *info);
int		handle_here(const char *delim);

//History
int		history_init(void);
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
int		ft_calc(t_shell *shell, int ac, char **av);

//Debug builtin
int		ft_debug(t_shell *shell, int ac, char **av);
void	cleanup_base(t_shell *shell);
void	clean_info(t_info **info);
void	clean_tokens(t_token **tokens);

//Signals
void	handle_control_d(t_shell *shell);

//Environment lst utils
t_env	*env_addpair(char *key, char *value, t_envtype type);
t_env	*env_lstback(t_env **env);
// t_env	*env_lstrepl_value(t_env **lst, char *key, char *value);
void	env_lstrepl_value(t_env **lst, char *key, char *value);
void	env_lstaddback(t_env **env, t_env *new);
void	env_lstdelone(t_env **env, char *key);

//Exp v2
t_env	*find_pair(t_shell *shell, char *key);
char	*find_pair_list(t_env **env, char *key);
char	*find_pair_content(t_shell *shell, char *key);
void	set_pairv2(t_shell *shell, char *key, char *value, t_envtype type);
void	sed_pair(t_shell *shell, char *key, char *value, t_envtype type);

// More lst functions
void	info_addback(t_info **info, t_info *new);

#endif
