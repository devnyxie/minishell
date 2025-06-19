/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:10:24 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/16 14:40:15 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "exec_cmd/exec_cmd.h"
# include "libft/libft.h"
# include "parser/parser.h"
# include "structs.h"
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>

// builtins
int		builtin_cd(t_shell *shell, char **args);
int		builtin_echo(char **args);
int		builtin_pwd(char **args);
int		builtin_exit(t_shell *shell, char **args);
int		builtin_env(t_shell *shell);
int		builtin_export(t_shell *shell, char **args);
int		builtin_unset(t_shell *shell, char **args);
int 	exit_shell(char **args);
int 	execute_parent_builtin(t_shell *shell, char **args, t_cmd *cmd);
int     is_parent_builtin(t_shell *shell, t_cmd *cmd);
void	update_env_var(t_shell *shell, char *var_name, const char *value);
t_builtin	*init_builtins_parent(void);
t_builtin	*init_builtins_child(void);

// error_handling.c
void		custom_error(char *msg);

// utils
// utils/ft_strcpy.c
char		*ft_strcpy(char *s1, char *s2);
// utils/ft_strcmp.c
int			ft_strcmp(char *s1, char *s2);
// utils/init_shell.c
t_shell		*init_shell(char **envp);
// utils/free_2d.c
void		free_2d(char **str);

//env
void	unset_env_var(char *name, t_shell *shell);
int		is_valid_identifier(char *name);

#endif