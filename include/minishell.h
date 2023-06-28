
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

typedef struct s_environment
{
	char					*key;
	char					*value;
	struct s_environment	*next;
}	t_env;

typedef struct s_shell
{
	char	*last_read_line;
	t_env	*environment;
}	t_shell;

t_env	*setup_environment(char **envp);

#endif
