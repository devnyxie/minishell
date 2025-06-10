/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:10:24 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/10 12:16:23 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "parser/parser.h"
# include <errno.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct		s_shell t_shell;
typedef int			(*t_builtin_fn)(t_shell *shell, char **args);

typedef struct s_builtin
{
	char			*name;
	t_builtin_fn	fn;
}					t_builtin;

// main shell structure
typedef struct s_shell
{
	char			**history;
	char *prompt; // raw input
	t_shell_input	*parsed_input;
	t_builtin		*builtins;
	char			**envp;
	char			*path;
	int				env_count;
	int				env_capacity;
}					t_shell;

// lexer.c
void				lexer(t_shell *shell, t_cmd *command);

// builtins
// builtins/exit.c
int		builtin_cd(t_shell *shell, char **args);
int		builtin_echo(char **args);
int		builtin_pwd(char **args);
int		builtin_exit(t_shell *shell, char **args);
int		builtin_env(t_shell *shell);
int		builtin_export(t_shell *shell, char **args);
int		builtin_unset(t_shell *shell, char **args);
int 	exit_shell(char **args);
int 	execute_builtin(t_shell *shell, char **args);
int 	is_builtin(t_shell *shell, char *cmd_name);
void	update_env_var(t_shell *shell, char *var_name, const char *value);

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
t_shell				*init_shell(char **envp);
// utils/init_builtins.c
t_builtin			*init_builtins(void);
// utils/free_2d.c
void	free_2d(char **str);

#endif