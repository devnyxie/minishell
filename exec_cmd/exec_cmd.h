/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:47:04 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/20 17:26:34 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_CMD_H
# define EXEC_CMD_H

# include "../minishell.h"
# include "../structs.h"
# include <sys/types.h>

typedef struct s_procctx
{
	t_cmd	*cmd;
	t_shell	*shell;
	char	**args;
	int		prev_fd;
	int		pipefd[2];
	pid_t	pid;
}			t_procctx;

void		exec_cmd(t_cmd *cmd, t_shell *shell, char **args);
void		child_process(t_cmd *cmd, int prev_fd, int pipefd[2],
				t_shell *shell);
char		*search_cmd_path(char *path, char *cmd);
int			start_process(t_cmd *cmd, int prev_fd, t_shell *shell, char **args);
int			try_builtin_child(t_shell *shell, t_cmd *cmd);
void		exec_absolute_path(t_shell *shell, t_cmd *cmd);
void		exec_relative_path(t_shell *shell, t_cmd *cmd);
void		handle_input_redirection(t_redirect *redir);
#endif