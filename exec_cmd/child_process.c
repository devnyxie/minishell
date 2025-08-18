/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:33:33 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/14 15:36:40 by tafanasi         ###   ########.fr       */
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
	t_redirect	*redir;
	int			fd;

	// Handle heredoc first if present
	if (cmd->in_fd != -1)
	{
		dup2(cmd->in_fd, STDIN_FILENO);
		close(cmd->in_fd);
		cmd->in_fd = -1;
	}
	
	// Then handle other input redirections
	redir = cmd->in_redir;
	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			fd = open(redir->file, O_RDONLY);
			if (fd < 0)
			{
				report_error(NULL, redir->file, 1);
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
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
	char	*path;
	int		i;

	i = 0;
	while (shell->builtins->builtins_child[i].name)
	{
		if (ft_strcmp(cmd->name, shell->builtins->builtins_child[i].name) == 0)
		{
			shell->builtins->builtins_child[i].fn(shell, cmd->args);
			free_shell(shell);
			exit(0);
		}
		i++;
	}
	path = search_cmd_path(shell->path, cmd->name);
	if (path)
	{
		execve(path, cmd->args, shell->envp);
		perror("execve");
		free(path);
	}
	else
		report_error(cmd->name, "command not found", 0);
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
