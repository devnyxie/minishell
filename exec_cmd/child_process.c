/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:33:33 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/22 12:54:04 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"

static void	child_process_prepare(t_cmd *cmd, int prev_fd, int pipefd[2])
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
}

static void	child_process_redir_in(t_cmd *cmd)
{
	if (cmd->in_fd != -1)
	{
		dup2(cmd->in_fd, STDIN_FILENO);
		close(cmd->in_fd);
		cmd->in_fd = -1;
	}
	handle_input_redirection(cmd->in_redir);
}

static void	child_process_redir_out(t_cmd *cmd)
{
	t_redirect	*redir;
	int			fd;

	redir = cmd->out_redir;
	while (redir)
	{
		if (redir->type == REDIR_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == REDIR_APPEND)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			report_error(NULL, redir->file, 1);
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
}

static void	child_process_exec(t_shell *shell, t_cmd *cmd)
{
	if (!cmd->name || cmd->name[0] == '\0')
	{
		free_shell(shell);
		exit(0);
	}
	try_builtin_child(shell, cmd);
	if (cmd->name[0] == '/')
		exec_absolute_path(shell, cmd);
	else
		exec_relative_path(shell, cmd);
}

void	child_process(t_cmd *cmd, int prev_fd, int pipefd[2], t_shell *shell)
{
	child_process_prepare(cmd, prev_fd, pipefd);
	child_process_redir_in(cmd);
	child_process_redir_out(cmd);
	child_process_exec(shell, cmd);
	free_shell(shell);
	exit(1);
}
