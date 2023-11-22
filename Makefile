NAME = minishell

# Sum commands
RM = rm -rf
MKDIR = mkdir -p
MAKE = make --silent

# Compiler
CC = gcc -g
CFLAGS = -fstack-usage #-fsanitize=address #-Wall -Werror -Wextra

# Color definitions
GREEN = \033[0;92m
RESET = \033[0m

# Folders
SRC_DIR = ./src
OBJ_DIR = ./bin
INC_DIR = ./include

# Lib folders
LIBFT = ./libft

# Library flags
READLINE_L = -lreadline

# Files
FILES	=	ft_freedoublearray \
			ft_isnull \
			ft_split_space \
			ft_safe_strdup \
			ft_split_first_occurence \
			ft_unset \
			ft_export \
			ft_echo \
			ft_cd \
			ft_env \
			ft_exit \
			ft_pwd \
			ft_debug \
			builtin \
			executor2 \
			executor_utils \
			fd_handling \
			lexer_lst \
			lexer \
			lexer_helpers \
			lexer_utils \
			lexer_debug \
			history \
			main \
			signals \
			readline \
			parser \
			parser_utils \
			parser_helpers \
			environment \
			environment_lst \
			parser_lst \
			garbage_collector \
			ft_replace \
	
HEADER	=	./include/minishell.h \
			./include/colors.h \
			./include/tokens.h \
			./include/libft.h \

vpath %.c	$(SRC_DIR) $(SRC_DIR)/builtins $(SRC_DIR)/parser $(SRC_DIR)/executor $(SRC_DIR)/lists $(SRC_DIR)/lexer $(SRC_DIR)/libft_funcs

SRC 	= ${addsuffix .c, $(FILES)}
OBJ 	= ${patsubst %.c, $(OBJ_DIR)/%.o, $(SRC)}

# Rules
all: $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
	@echo "$(GREEN)Compiling: $(RESET)$(notdir $<)"

$(NAME): $(OBJ) $(HEADER) | lib
	@$(CC) $(CFLAGS) $(OBJ) -I$(INC_DIR) $(LIBFT)/libft.a $(READLINE_L) -o $(NAME)
	@echo "$(GREEN)Compiling: $(RESET)$(NAME)"

$(OBJ_DIR):
	@$(MKDIR) -p $(OBJ_DIR)

lib:
	@$(MAKE) -C $(LIBFT)

clean:
	@$(MAKE) clean -C $(LIBFT)
	@$(RM) $(OBJ) $(OBJ_DIR)
	@echo "Cleaning"

fclean: clean
	@$(MAKE) fclean -C $(LIBFT)
	@$(RM) $(NAME)
	@echo "Cleaning"

re: fclean all

dev:
	gcc test/main.c test/testshell.h test/print.c -I./include -lft -lreadline -L./libft

.PHONY: all lib clean fclean re