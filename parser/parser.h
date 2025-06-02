/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:14:47 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/02 12:41:41 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

typedef enum e_redirect_type
{
	REDIR_IN,     // <
	REDIR_OUT,    // >
	REDIR_APPEND, // >>
	HEREDOC       // <<
}						t_redirect_type;

typedef struct s_redirect
{
	t_redirect_type		type;
	char				*file;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_cmd
{
	char				*name;
	char **args;           // argv-like
	t_redirect *in_redir;  // linked list of input redirs
	t_redirect *out_redir; // linked list of output redirs
	struct s_cmd *next;    // for pipelines: `cmd1 | cmd2 | cmd3`
}						t_cmd;

typedef struct s_shell_input
{
	t_cmd				*first_cmd;
	t_cmd				*last_cmd;
	int is_valid; // optional, can be useful
	char				*input;
}						t_shell_input;

// parser.c
t_shell_input			*parser(char *input);
void					free_shell_input(t_shell_input *input);

#endif