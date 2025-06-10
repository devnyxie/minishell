/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:15:33 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/10 17:15:56 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_cmd_path(char *path, char *cmd)
{
	char	**paths;
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	paths = ft_split(path, ':');
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
			break ;
		tmp = ft_strjoin(full_path, cmd);
		free(full_path);
		if (!tmp)
			break ;
		if (access(tmp, X_OK) == 0)
		{
			free_2d(paths);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}

// Recursively launch each command in the pipeline.
// 'prev_fd' is the read end of the previous pipe (or -1 for the first command).
int	start_process(t_cmd *cmd, int prev_fd, t_shell *shell)
{
	int	pipefd[2] = {-1, -1};
	int	pid;

	if (pid == 0)
		child_process(cmd, prev_fd, pipefd, shell);
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->next)
	{
		close(pipefd[1]);
	}
	if (cmd->next)
	{
		start_process(cmd->next, pipefd[0], shell);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

// gets parsed input from shell->parsed_input and starts the commands
void	lexer(t_shell *shell, t_cmd *cmd)
{
	start_process(cmd, -1, shell);
}