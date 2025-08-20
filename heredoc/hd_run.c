/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:08:01 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/20 14:50:15 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include <readline/readline.h>

static int	is_limiter(char *s, char *lim)
{
	if (!s || !lim)
		return (0);
	return (ft_strcmp(s, lim) == 0);
}

static int	open_pipe(int fd[2])
{
	if (pipe(fd) == -1)
		return (-1);
	return (0);
}

static int	write_line(int wfd, const char *line, int expand, t_shell *sh)
{
	if (hd_write_expanded_line(wfd, line, expand, sh) < 0)
		return (-1);
	if (write(wfd, "\n", 1) != 1)
		return (-1);
	return (0);
}

int	run_single_heredoc(t_redirect *r, t_shell *sh)
{
	int		fd[2];
	char	*line;

	if (open_pipe(fd) < 0)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || is_limiter(line, r->file))
			break ;
		if (write_line(fd[1], line, r->expand, sh) < 0)
		{
			free(line);
			close(fd[0]);
			close(fd[1]);
			return (-1);
		}
		free(line);
	}
	free(line);
	close(fd[1]);
	return (fd[0]);
}
