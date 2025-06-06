/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:10:24 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/03 17:46:29 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <errno.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// todo:
# include "parser/parser.h"

typedef int			(*t_builtin_fn)(char **args);

typedef struct s_builtin
{
	char			*name;
	t_builtin_fn	fn;
}					t_builtin;

// main shell structure
typedef struct s_shell
{
	char **			history;
	char *			prompt; //raw input
	t_shell_input	*parsed_input;
	t_builtin		*builtins;
	char			**envp;
}					t_shell;

// lexer.c
void				lexer(char *command, char **args);

// builtins
// builtins/exit.c
int					exit_shell(char **args);
int					builtin_echo(char **args);
int					builtin_pwd(char **args);

// error_handling.c
void				custom_error(char *msg);

// utils
// utils/ft_strcpy.c
char				*ft_strcpy(char *s1, char *s2);
// utils/ft_strcmp.c
int					ft_strcmp(char *s1, char *s2);
// utils/is_space.c
int					is_space(char c);
// utils/skip_space.c
void				skip_space(char **input);
// utils/grab_word.c
char				*grab_word(char **input);
// utils/init_shell.c
t_shell				*init_shell(void);
// utils/init_builtins.c
t_builtin			*init_builtins(void);

#endif