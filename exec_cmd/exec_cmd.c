/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:04:38 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/20 15:53:57 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exec_cmd.h"

int	open_redir_file(t_redirect *redir)
{
	int	fd;

	if (redir->type == REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (-1);
	if (fd < 0)
	{
		report_error(NULL, redir->file, 1);
		exit(1);
	}
	return (fd);
}

void	exec_cmd(t_cmd *cmd, t_shell *shell, char **args)
{
	if (prepare_heredocs(cmd, shell) < 0)
	{
		shell->exit_code = 1;
		return ;
	}
	prune_heredocs(cmd);
	start_process(cmd, -1, shell, args);
}
