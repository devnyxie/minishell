/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:47:04 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/12 12:04:29 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_CMD_H
# define EXEC_CMD_H

# include "../minishell.h"
# include "../structs.h"
// # include "../parser/parser.h"
// typedef struct s_shell	t_shell;

void	exec_cmd(t_cmd *cmd, t_shell *shell, char **args);
void	child_process(t_cmd *cmd, int prev_fd, int pipefd[2], t_shell *shell);
char	*search_cmd_path(char *path, char *cmd);
int		start_process(t_cmd *cmd, int prev_fd, t_shell *shell, char **args);
#endif