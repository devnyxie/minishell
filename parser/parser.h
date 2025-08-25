/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:14:47 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/22 15:43:30 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

typedef struct s_cmd_params
{
	t_shell_input	*shell_input;
	char			**envp;
	t_shell			*shell;
}	t_cmd_params;

typedef struct s_redirect_info
{
	char			*name;
	t_redirect_type	type;
	int				expand;
	t_cmd			*cmd;
	t_shell_input	*shell_input;
}	t_redirect_info;

// parser.c
void			parser(t_shell *shell, char *input);
// parser_cmd.c
void			handle_cmd(t_shell_input *shell_input, char **envp,
					t_shell *shell);
void			append_to_linked_list(t_shell_input *shell_input, t_cmd *cmd);
// skip_space.c
void			skip_space(char **input);
// is_space.c
int				is_space(char c);
// grab_word.c
char			*grab_word(char **input);
char			*grab_word_with_env(char **input, char **envp, t_shell *shell);
// expansion_helpers.c
int				process_exit_code_length(t_shell *shell);
int				process_variable_length(char *word, int *i, char **envp);
int				calculate_expanded_length(char *word, char **envp,
					t_shell *shell);
// word_expansion.c
void			copy_exit_code(char **dst, t_shell *shell);
void			copy_env_variable(char **src, char **dst, char **envp);
char			*expand_unquoted_variables(char *word, char **envp,
					t_shell *shell);
// quote_handler.c
char			*grab_quoted_word(char **input, char **envp, t_shell *shell);
char			*grab_single_quoted_word(char **input);
int				has_unclosed_quotes(char *input);
char			*expand_variable_in_quotes(char **input, char **envp,
					t_shell *shell);
// quote_processing.c
char			*find_quote_end(char *start);
char			*process_quoted_content(char *input, char **envp,
					t_shell *shell);
// variable_expansion.c
char			*handle_special_variable(char *var_name, t_shell *shell,
					char **input, int var_len);
char			*get_variable_name(char **input, int *var_len);

// quote_utils
int				is_escaped_char(char c);
char			handle_escape_in_quotes(char **input);
int				find_var_end(char *input);
// quote_calculation.c
size_t			handle_escape_length(char **temp_input);
size_t			handle_variable_length(char **temp_input, char **envp,
					t_shell *shell);
size_t			calculate_quoted_length(char *input, char **envp,
					t_shell *shell);

// redirection_parse.c
t_redirect_type	redirect_type(t_shell_input *shell_input, t_cmd *cmd);
void			handle_redirect(t_shell_input *shell_input);
// string_utils.c
int				str_len_inside_quotes(char **p, char q);
char			*allocate_and_copy(char *start, size_t len);
char			*read_quoted_str(char **p);
// redirect_helpers.c
t_cmd			*create_empty_cmd(t_shell_input *shell_input);
int				validate_redirect_name(char *name, t_shell_input *shell_input);
void			create_and_add_redirect(t_redirect_info *info);

// redirection_utils.c
t_redirect		*new_redirect_node(t_redirect_type type, char *file);
void			add_redirect_to_cmd(t_cmd *cmd, t_redirect *redir);
void			prune_heredocs(t_cmd *cmds);

#endif
