CC = cc
CFLAGS = -Wall -Wextra -Werror -include minishell.h -include parser/parser.h

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = minishell.c \
		lexer.c \
		error_handling.c \
		builtins/builtin_env.c \
		builtins/builtin_exit.c \
		builtins/builtin_export.c \
		builtins/builtin_cd.c \
		builtins/builtin_echo.c \
		builtins/builtin_pwd.c \
		builtins/is_builtin.c \
		parser/parser.c \
		parser/parser_cmd.c \
		parser/parser_mem.c \
		utils/ft_strcpy.c \
		utils/ft_strcmp.c \
		utils/is_space.c \
		utils/skip_space.c \
		utils/grab_word.c \
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