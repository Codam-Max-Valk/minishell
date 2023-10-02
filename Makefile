NAME = minishell

# Sum commands
RM = rm -rf
MKDIR = mkdir -p
MAKE = make --silent

# Compiler
CC = gcc
CFLAGS = -g #-Wall -Werror -Wextra

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
			ft_isspace \
			ft_realloc \
			ft_split_space \
			ft_strcmp \
			ft_strstr \
			ft_safe_strdup \
			ft_split_first_occurence \
			ft_unset \
			ft_export \
			ft_echo \
			ft_cd \
			ft_env \
			ft_exit \
			ft_pwd \
			ft_calc \
			ft_debug \
			builtin \
			builtin_utils \
			executor \
			lexer_lst \
			lexer \
			lexer_helpers \
			lexer_utils \
			history \
			main \
			signals \
			readline \
			parser \
			environment \
			environment_lst \
	
HEADER	=	./include/minishell.h \
			./include/colors.h \
			./include/tokens.h \
			./include/libft.h \

vpath %.c	$(SRC_DIR) $(SRC_DIR)/builtins $(SRC_DIR)/executor $(SRC_DIR)/lists $(SRC_DIR)/lexer $(SRC_DIR)/libft_funcs

SRC 	= ${addsuffix .c, $(FILES)}
OBJ 	= ${patsubst %.c, $(OBJ_DIR)/%.o, $(SRC)}

# Rules
all: $(NAME)
	#@./$(NAME)

$(OBJ_DIR)/%.o: %.c | bin
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
	@echo "$(GREEN)Compiling: $(RESET)$(notdir $<)"

$(NAME): $(OBJ) $(HEADER) | lib
	@$(CC) $(CFLAGS) $(OBJ) -I$(INC_DIR) $(LIBFT)/libft.a $(READLINE_L) -o $(NAME)
	@echo "$(GREEN)Compiling: $(RESET)$(NAME)"

bin:
	@$(MKDIR) $(OBJ_DIR)

lib:
	@$(MAKE) -C $(LIBFT)

clean:
	@$(MAKE) clean -C $(LIBFT)
	@$(RM) $(OBJ)
	@$(RM) $(OBJ_DIR)
	@echo "Cleaning"

fclean: clean
	@$(MAKE) fclean -C $(LIBFT)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all lib clean fclean re bin
