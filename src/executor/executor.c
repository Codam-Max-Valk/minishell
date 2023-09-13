
//#include "minishell.h"

//typedef	struct s_file_node	t_file_node;

//typedef struct s_info
//{
//	char			**command;
//	t_list			*inf;
//	t_list			*outf;
//	int				fd_in;
//	int				fd_out;
//	struct s_info	*next;
//	struct s_info	*prev;
//}	t_info;

//typedef	struct s_file_node
//{
//	char 		*file_name;
//	t_tag 		type;
//}	t_file_node;

//int	handle_here()
//{
//	return (STDIN_FILENO);
//}

//void	set_start_fd(t_info *info)
//{
//	t_file_node	*tmp;

//	while (info->inf != NULL)
//	{
//		tmp = info->inf->content;
//		if (tmp->type == T_REDIRECT_IN)
//			info->fd_in = open(tmp->file_name, O_RDONLY);
//		else if (tmp->type == T_HERE_DOC)
//			info->fd_in = handle_here();
//		if (info->fd_in == -1)
//			perror("infile not open");
//		info->inf = info->inf->next;
//	}
//	while (info->outf != NULL)
//	{
//		tmp = info->outf->content;
//		if (tmp->type == T_APPEND)
//			info->fd_out = open(tmp->file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
//		else if (tmp->type == T_REDIRECT_OUT)
//			info->fd_out = open(tmp->file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
//		if (info->fd_out == -1)
//			perror("outfile not open");
//		info->outf = info->outf->next;
//	}
//}

//char	**parse_env(char **envp)
//{
//	char	**split_path;
//	int		i;

//	i = 0;
//	while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
//		i++;
//	split_path = ft_split(envp[i], ':');
//	return (split_path);
//}

//char	*cmd_path(char **paths, char *cmd, int path_f)
//{
//	char	*full_cmd;
//	char	*tmp;

//	if (!cmd)
//		return (NULL);
//	if (ft_strchr(cmd, '/'))
//		return (cmd);
//	if (path_f == -1)
//		return (NULL);
//	while (*paths)
//	{
//		tmp = ft_strjoin(*paths, "/");
//		full_cmd = ft_strjoin(tmp, cmd);
//		free (tmp);
//		if (access(full_cmd, F_OK) == 0)
//			return (full_cmd);
//		free (full_cmd);
//		paths++;
//	}
//	return (NULL);
//}

//void	error_exit(char *function, int error_num)
//{
//	perror(function);
//	exit(error_num);
//}

//void	execute_command(t_info *info, char *envp[])
//{
//	pid_t	pid;
//	char	*cmd_p;

//	pid = fork();
//	if (pid == -1)
//		exit(EXIT_FAILURE);
//	if (pid == 0)
//	{
//		set_start_fd(info);
//		if (info->fd_in != STDIN_FILENO)
//		{
//			if (dup2(info->fd_in, STDIN_FILENO) < 0)
//				error_exit("dup2", errno);
//			close(info->fd_in);
//		}		
//		if (info->fd_out != STDOUT_FILENO)
//		{
//			if (dup2(info->fd_out, STDOUT_FILENO) < 0)
//				error_exit("dup2", errno);
//			close(info->fd_out);
//		}
//		cmd_p = cmd_path(parse_env(envp), info->command[0], 1);
//		if (execve(cmd_p, info->command, envp) < 0)
//			error_exit("execve", errno);
//	}
//	else
//		waitpid(pid, NULL, 0);
//}

//void	exec_loop(t_info *info, char *envp[])
//{
//	int		pipe_fd[2];
//	t_info	*current_cmd;

//	info->fd_in = STDIN_FILENO;
//	if (info && info->next != NULL)
//		if (pipe(pipe_fd) == -1)
//			perror("pipe");
//	while (info != NULL)
//	{
//		current_cmd = info;
//		info = info->next;
//		if (info != NULL)
//			current_cmd->fd_out = pipe_fd[1];
//		else
//			current_cmd->fd_out = STDOUT_FILENO;
//		execute_command(current_cmd, envp);
//		if (info != NULL)
//		{
//			close(current_cmd->fd_out);
//			info->fd_in = pipe_fd[0];
//		}
//	}
//	close(pipe_fd[0]);
//}

////int main(int ac, char **av, char *envp[])
////{
////	// t_file_node file1 = {"here", T_HERE_DOC};
////	// t_file_node file2 = {"in", T_REDIRECT_IN};
////	char	*s = "cat";
////	t_info *a = calloc(1, sizeof(t_info));
////	t_file_node file3 = {"out", T_REDIRECT_OUT};
////	t_file_node file4 = {"oapp", T_APPEND};
////	t_info *b = calloc(1, sizeof(t_info));
////	t_file_node file5 = {"out2", T_REDIRECT_OUT};
////	t_file_node file6 = {"oapp2", T_APPEND};
////	b->command = calloc(3, sizeof(char *));
////	b->command[0] = s;
////	b->outf = ft_lstnew(&file5);
////	ft_lstadd_back(&b->outf, ft_lstnew(&file6));
////	(void)ac;
////	// (void)av;
////	// a->inf = ft_lstnew(&file1);
////	// ft_lstadd_back(&a->inf, ft_lstnew(&file2));
////	a->command = &av[1];
////	a->next = b;
////	a->outf = ft_lstnew(&file3);
////	ft_lstadd_back(&a->outf, ft_lstnew(&file4));
////	exec_loop(a, envp);
////	return (0);
////}

/*

>>cat < Makefile | grep > out -v "MAKE"
TAG: COMMAND            => CONTENT: cat
TAG: REDIRECT_IN        => CONTENT: Makefile
TAG: PIPE               => CONTENT: |
TAG: COMMAND            => CONTENT: grep
TAG: REDIRECT_OUT       => CONTENT: out -v
TAG: DOUBLE_QUOTE       => CONTENT: MAKE

*/