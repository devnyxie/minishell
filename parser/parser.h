/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:14:47 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/22 12:54:04 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

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
// quote_handler.c
char			*grab_quoted_word(char **input, char **envp, t_shell *shell);
char			*grab_single_quoted_word(char **input);
int				has_unclosed_quotes(char *input);

// redirection_parse.c
t_redirect_type	redirect_type(t_shell_input *shell_input, t_cmd *cmd);
void			handle_redirect(t_shell_input *shell_input);

// redirection_utils.c
t_redirect		*new_redirect_node(t_redirect_type type, char *file);
void			add_redirect_to_cmd(t_cmd *cmd, t_redirect *redir);
void			prune_heredocs(t_cmd *cmds);

#endif
