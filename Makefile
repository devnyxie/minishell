CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = minishell.c lexer.c error_handling.c builtins/exit.c parser/parser.c
OBJ = $(SRC:.c=.o)
NAME = minishell

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline

# Compile object files
%.o: %.c minishell.h parser/parser.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compile libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Clean obj files
clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJ)

# Clean everything (lib and obj)
fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re