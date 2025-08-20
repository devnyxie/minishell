/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_apply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:15:44 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/20 14:53:28 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

int	prepare_heredocs(t_cmd *cmds, t_shell *sh)
{
	t_cmd		*c;
	t_redirect	*r;
	int			fd;

	c = cmds;
	while (c)
	{
		r = c->in_redir;
		while (r)
		{
			if (r->type == HEREDOC)
			{
				fd = run_single_heredoc(r, sh);
				if (fd < 0)
					return (-1);
				if (c->in_fd != -1)
					close(c->in_fd);
				c->in_fd = fd;
			}
			r = r->next;
		}
		c = c->next;
	}
	return (0);
}
