/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:41:01 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/20 16:41:02 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

t_redirect	*new_redirect_node(t_redirect_type type, char *file)
{
	t_redirect	*redir;

	redir = (t_redirect *)malloc(sizeof(t_redirect));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = file;
	redir->expand = 0;
	redir->next = NULL;
	return (redir);
}

void	add_redirect_to_cmd(t_cmd *cmd, t_redirect *redir)
{
	t_redirect	**head;
	t_redirect	*cur;

	if (redir->type == REDIR_IN || redir->type == HEREDOC)
		head = &cmd->in_redir;
	else
		head = &cmd->out_redir;
	if (!*head)
	{
		*head = redir;
		redir->next = NULL;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = redir;
	redir->next = NULL;
}

void	prune_heredocs(t_cmd *cmds)
{
	t_cmd		*c;
	t_redirect	**pp;
	t_redirect	*dead;

	c = cmds;
	while (c)
	{
		pp = &c->in_redir;
		while (*pp)
		{
			if ((*pp)->type == HEREDOC)
			{
				dead = *pp;
				*pp = (*pp)->next;
				free(dead->file);
				free(dead);
			}
			else
				pp = &(*pp)->next;
		}
		c = c->next;
	}
}
