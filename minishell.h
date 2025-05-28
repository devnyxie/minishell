/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:10:24 by tafanasi          #+#    #+#             */
/*   Updated: 2025/05/28 13:48:39 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_command
{
	char			*name;
	int				n_args;
	char			**args;
}					t_command;

typedef int			(*t_builtin_fn)(char **args);

typedef struct s_builtin
{
	char			*name;
	t_builtin_fn	fn;
}					t_builtin;

void				lexer(char *command, char **args);
int					exit_shell(char **args);
void				custom_error(char *msg);
int					parser(char *input);

#endif