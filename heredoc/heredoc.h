/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:16:29 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/20 15:09:43 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "../minishell.h"
# include "../structs.h"
# include <stddef.h>
# include <unistd.h>

typedef struct s_hdctx
{
	int			fd; // write target
	const char	*line; // current input line
	size_t		i; // current indec
	size_t		chunk; // last chunk start
	t_shell		*sh; // shell for env
}				t_hdctx;

/* small utils shared across heredoc files */
int	hd_write_str(int fd, const char *s, size_t n);
int	hd_write_status(int fd, int code);

/* expand and write one line to fd */
int	hd_write_expanded_line(int fd, const char *line, int expand, t_shell *sh);

/* one heredoc -> returns read end fd, or -1 on error */
int	run_single_heredoc(t_redirect *r, t_shell *sh);

/* walk commands and prepare all heredocs */
int	prepare_heredocs(t_cmd *cmds, t_shell *sh);

#endif