/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:14:47 by tafanasi          #+#    #+#             */
/*   Updated: 2025/07/05 19:20:07 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "../minishell.h"

// typedef enum e_redirect_type
// {
// 	REDIR_IN,
// 	REDIR_OUT,
// 	REDIR_APPEND,
// 	HEREDOC
// }						t_redirect_type;

// typedef struct s_redirect
// {
// 	t_redirect_type		type;
// 	char				*file;
// 	struct s_redirect	*next;
// }						t_redirect;

// typedef struct s_cmd
// {
// 	char				*name;
// 	char				**args;
// 	t_redirect			*in_redir;
// 	t_redirect			*out_redir;
// 	struct s_cmd		*next;
// 	struct s_cmd		*prev;
// 	int					pipe_read;
// }						t_cmd;

// typedef struct s_shell_input
// {
// 	t_cmd				*first_cmd;
// 	t_cmd				*last_cmd;
// 	int					cmds_count;
// 	int					is_valid;
// 	char				*input;
// }						t_shell_input;

// parser.c
void parser(t_shell *shell, char *input);
// parser_cmd.c
void handle_cmd(t_shell_input *shell_input);
// parser_mem.c
void free_shell_input(t_shell_input *input);
// skip_space.c
void skip_space(char **input);
// is_space.c
int is_space(char c);
// grab_word.c
char *grab_word(char **input);

#endif