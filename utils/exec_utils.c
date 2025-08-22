/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:54:04 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/22 12:54:04 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_cmd/exec_cmd.h"

int	try_builtin_child(t_shell *shell, t_cmd *cmd)
{
	int	i;

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
	return (0);
}

void	exec_absolute_path(t_shell *shell, t_cmd *cmd)
{
	if (access(cmd->name, F_OK) == 0)
	{
		if (access(cmd->name, X_OK) == 0)
		{
			execve(cmd->name, cmd->args, shell->envp);
			perror("execve");
		}
		else
			report_error(cmd->name, "Permission denied", 0);
	}
	else
		report_error(cmd->name, "No such file or directory", 127);
}

void	exec_relative_path(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	if (shell->path == NULL)
		report_error(cmd->name, "command not found", 0);
	else
	{
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
}

void	handle_input_redirection(t_redirect *redir)
{
	int	fd;

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
