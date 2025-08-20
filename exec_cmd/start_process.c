/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:18:09 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/20 17:49:11 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"

static void	close_fds(int prev_fd, t_cmd *cmd, int pipefd[2])
{
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->next)
		close(pipefd[1]);
}

static int	exec_parent_builtin(t_procctx *p)
{
	if (is_parent_builtin(p->shell, p->cmd))
	{
		execute_parent_builtin(p->shell, p->args, p->cmd);
		return (1);
	}
	return (0);
}

static void	setup_and_fork(t_procctx *p)
{
	if (p->cmd->next)
	{
		if (pipe(p->pipefd) < 0)
		{
			perror("pipe");
			exit(1);
		}
	}
	p->pid = fork();
	if (p->pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (p->pid == 0)
		child_process(p->cmd, p->prev_fd, p->pipefd, p->shell);
}

static void	parent_join_and_cleanup(t_procctx *p)
{
	int	status;
	int	exit_code;

	close_fds(p->prev_fd, p->cmd, p->pipefd);
	if (p->cmd->next)
		start_process(p->cmd->next, p->pipefd[0], p->shell, p->args);
	waitpid(p->pid, &status, 0);
	if (p->cmd->in_fd != -1)
	{
		close(p->cmd->in_fd);
		p->cmd->in_fd = -1;
	}
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		p->shell->exit_code = exit_code;
	}
}

int	start_process(t_cmd *cmd, int prev_fd, t_shell *shell, char **args)
{
	t_procctx	p;

	p.cmd = cmd;
	p.shell = shell;
	p.args = args;
	p.prev_fd = prev_fd;
	p.pipefd[0] = -1;
	p.pipefd[1] = -1;
	if (exec_parent_builtin(&p))
		return (0);
	setup_and_fork(&p);
	parent_join_and_cleanup(&p);
	return (0);
}
