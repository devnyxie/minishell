/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:10:24 by tafanasi          #+#    #+#             */
/*   Updated: 2025/07/23 11:36:07 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "exec_cmd/exec_cmd.h"
# include "libft/libft.h"
# include "parser/parser.h"
# include "structs.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// builtins
int				builtin_cd(t_shell *shell, char **args);
int				builtin_echo(char **args);
int				builtin_pwd(char **args);
int	builtin_exit(t_shell *shell, char **args); // to-be-reviewed
int				builtin_env(t_shell *shell, char **args);
int				builtin_export(t_shell *shell, char **args);
int				builtin_unset(t_shell *shell, char **args);
int				exit_shell(char **args);
int				execute_parent_builtin(t_shell *shell, char **args, t_cmd *cmd);
int				is_parent_builtin(t_shell *shell, t_cmd *cmd);
void			update_env_var(t_shell *shell, char *var_name,
					const char *value);

// env
int				env_count(char **envp);

// error_handling.c
void			custom_error(char *msg);
void			report_error(char *command, char *detail, int is_sys_err);

// utils
char			*ft_strcpy(char *s1, char *s2);
int				ft_strcmp(char *s1, char *s2);
void			*ft_realloc(void *old, size_t new_size);
char			*ft_strndup(const char *s, size_t n);

// utils/init
t_shell			*init_shell(char **envp);
t_shell_input	*init_shell_input(char *input);
t_builtin		*init_builtins_parent(void);
t_builtin		*init_builtins_child(void);
t_cmd			*init_cmd(char *cmd_name);

// utils/cleanup
void			free_2d(char **str);
void			free_shell_input(t_shell_input *shell_input);
void			free_cmds(t_cmd *cmd);
void			free_redirects(t_redirect *redir);
void			free_builtins(t_builtins_unified *builtins);
void			free_shell(t_shell *shell);

// env
void			unset_env_var(char *name, t_shell *shell);
int				is_valid_identifier(char *name);

// parser/expanders
void	handle_expand_variables(char **envp, t_shell_input *shell_input);
// parser/parser
char	*get_env_value(char **envp, const char *key);
// parser/redirections
void	handle_redirect(t_shell_input *shell_input);
t_redirect_type	redirect_type(t_shell_input *shell_input, t_cmd *cmd);


#endif