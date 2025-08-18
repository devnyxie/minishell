/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:18:09 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/14 15:36:40 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"

static void	create_pipe_if_needed(t_cmd *cmd, int pipefd[2])
{
	if (cmd->next)
	{
		if (pipe(pipefd) < 0)
		{
			perror("pipe");
			exit(1);
		}
	}
}

static void	close_fds(int prev_fd, t_cmd *cmd, int pipefd[2])
{
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->next)
		close(pipefd[1]);
}

int	start_process(t_cmd *cmd, int prev_fd, t_shell *shell, char **args)
{
	int	pipefd[2] = {-1, -1};
	int	pid;
	int	status;
	int	exit_code;

	if (is_parent_builtin(shell, cmd))
		execute_parent_builtin(shell, args, cmd);
	else
	{
		create_pipe_if_needed(cmd, pipefd);
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(1);
		}
		if (pid == 0)
			child_process(cmd, prev_fd, pipefd, shell);
		close_fds(prev_fd, cmd, pipefd);
		if (cmd->next)
			start_process(cmd->next, pipefd[0], shell, args);
		waitpid(pid, &status, 0);
		if (cmd->in_fd != -1)
		{
			close(cmd->in_fd);
			cmd->in_fd = -1;
		}
		if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);
			shell->exit_code = exit_code;
		}
	}
	return (0);
}
