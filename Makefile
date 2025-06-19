CC = cc
CFLAGS = -Wall -Wextra -Werror -include minishell.h -include parser/parser.h -include exec_cmd/exec_cmd.h -g

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = minishell.c \
		error_handling.c \
		builtins/builtin_cd.c \
		builtins/builtin_echo.c \
		builtins/builtin_env.c \
		builtins/builtin_exit.c \
		builtins/builtin_export.c \
		builtins/builtin_unset.c \
		builtins/builtin_pwd.c \
		builtins/is_parent_builtin.c \
		builtins/execute_parent_builtin.c \
		exec_cmd/search_cmd_path.c \
		exec_cmd/exec_cmd.c \
		exec_cmd/child_process.c \
		exec_cmd/start_process.c \
		parser/parser.c \
		parser/parser_cmd.c \
		parser/parser_mem.c \
		utils/ft_strcpy.c \
		utils/ft_strcmp.c \
		parser/is_space.c \
		parser/skip_space.c \
		parser/grab_word.c \
		utils/env_check.c \
		utils/init_shell.c \
		utils/init_builtins.c \
		utils/free_2d.c 

		
OBJ = $(SRC:.c=.o)
NAME = minishell

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "Compiling minishell..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline

# Compile object files
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Compile libft
$(LIBFT):
	@echo "Compiling libft..."
	@$(MAKE) -s -C $(LIBFT_DIR)

clean:
	@$(MAKE) -s clean -C $(LIBFT_DIR)
	@rm -f $(OBJ)

fclean: clean
	@$(MAKE) -s fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)


re: fclean all

.PHONY: all clean fclean re