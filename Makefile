CC = cc
CFLAGS = -Wall -Wextra -Werror -include minishell.h -include parser/parser.h

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = minishell.c \
		lexer.c \
		error_handling.c \
		builtins/exit.c \
		builtins/builtin_echo.c \
		parser/parser.c \
		parser/parser_memory.c \
		utils/ft_strcpy.c \
		utils/utils.c
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