/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:10:24 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/12 14:07:16 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

// Parser

typedef enum e_redirect_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
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
	char				**args;
	t_redirect			*in_redir;
	t_redirect			*out_redir;
	struct s_cmd		*next;
	struct s_cmd		*prev;
	int					pipe_read;
}						t_cmd;

typedef struct s_shell_input
{
	t_cmd				*first_cmd;
	t_cmd				*last_cmd;
	int					cmds_count;
	int					is_valid;
	char				*input;
}						t_shell_input;

// Shell
typedef struct s_shell	t_shell;
typedef int				(*t_builtin_fn)(t_shell *shell, char **args);

typedef struct s_builtin
{
	char				*name;
	t_builtin_fn		fn;
}						t_builtin;

typedef struct s_shell
{
	char				**history;
	char				*prompt;
	t_shell_input		*parsed_input;
	t_builtin			*builtins;
	char				**envp;
	char				*path;
	int					env_count;
	int					env_capacity;
}						t_shell;

#endif