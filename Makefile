CC = cc
CFLAGS = -Wall -Wextra -Werror -include minishell.h -include parser/parser.h -include exec_cmd/exec_cmd.h -g

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

BUILTINS_SRC = \
	builtins/builtin_cd.c \
	builtins/builtin_cd_helpers.c \
	builtins/builtin_cd_env.c \
	builtins/builtin_echo.c \
	builtins/builtin_env.c \
	builtins/builtin_exit.c \
	builtins/builtin_export.c \
	builtins/builtin_unset.c \
	builtins/builtin_pwd.c \
	builtins/is_parent_builtin.c \
	builtins/execute_parent_builtin.c

ENV_SRC = \
	env/env_check.c \
	env/env_utils.c

EXEC_CMD_SRC = \
	exec_cmd/search_cmd_path.c \
	exec_cmd/exec_cmd.c \
	exec_cmd/child_process.c \
	exec_cmd/start_process.c

PARSER_SRC = \
	parser/expanders.c \
	parser/grab_word.c \
	parser/word_expansion.c \
	parser/expansion_helpers.c \
	parser/parser.c \
	parser/parser_cmd.c \
	parser/is_space.c \
	parser/redirections_parse.c \
	parser/redirect_helpers.c \
	parser/string_utils.c \
	parser/redirections_utils.c \
	parser/skip_space.c \
	parser/quote_handler.c \
	parser/quote_processing.c \
	parser/variable_expansion.c \
	parser/quote_utils.c \
	parser/quote_calculation.c 
			

UTILS_SRC = \
	utils/ft_strcpy.c \
	utils/ft_strcmp.c \
	utils/ft_realloc.c \
	utils/ft_strndup.c \
	utils/count_args.c \
	utils/is_valid_number.c \
	utils/exec_utils.c

INIT_SRC = \
	utils/init/init_shell.c \
	utils/init/init_builtins.c \
	utils/init/init_shell_input.c \
	utils/init/init_cmd.c \

CLEANUP_SRC = \
	utils/cleanup/free_2d.c \
	utils/cleanup/free_shell.c \
	utils/cleanup/free_builtins.c \
	utils/cleanup/free_shell_input.c \
	utils/cleanup/free_cmds.c \
	utils/cleanup/free_redirects.c

HEREDOC_SRC = \
	heredoc/hd_apply.c \
	heredoc/hd_expand.c \
	heredoc/hd_run.c \
	heredoc/hd_utils.c 

SRC = \
	minishell.c \
	input_handling.c \
	error_handling.c \
	$(BUILTINS_SRC) \
	$(ENV_SRC) \
	$(EXEC_CMD_SRC) \
	$(PARSER_SRC) \
	$(UTILS_SRC) \
	$(INIT_SRC) \
	$(CLEANUP_SRC) \
	$(HEREDOC_SRC) 

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
