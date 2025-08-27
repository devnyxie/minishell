/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_store.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:45:00 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/27 15:45:00 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

static void	add_to_pending_input(t_shell_input *shell_input, t_redirect *redir)
{
	t_redirect	*cur;

	if (!shell_input->pending_in_redir)
		shell_input->pending_in_redir = redir;
	else
	{
		cur = shell_input->pending_in_redir;
		while (cur->next)
			cur = cur->next;
		cur->next = redir;
	}
}

static void	add_to_pending_output(t_shell_input *shell_input, t_redirect *redir)
{
	t_redirect	*cur;

	if (!shell_input->pending_out_redir)
		shell_input->pending_out_redir = redir;
	else
	{
		cur = shell_input->pending_out_redir;
		while (cur->next)
			cur = cur->next;
		cur->next = redir;
	}
}

void	store_pending_redirect(t_shell_input *shell_input,
		t_redirect_params *params)
{
	t_redirect	*redir;

	if (params->fd != -1)
		redir = new_redirect_node_with_fd(params->type, params->name,
				params->fd);
	else
		redir = new_redirect_node(params->type, params->name);
	if (!redir)
	{
		shell_input->is_valid = 0;
		return ;
	}
	if (params->type == HEREDOC)
		redir->expand = params->expand;
	if (params->type == REDIR_IN || params->type == HEREDOC)
		add_to_pending_input(shell_input, redir);
	else
		add_to_pending_output(shell_input, redir);
}

void	set_redirect_fd_on_cmd(t_cmd *cmd, int fd, t_redirect_type type)
{
	t_redirect	*redir;

	if (fd == -1)
		return ;
	if (type == REDIR_OUT || type == REDIR_APPEND)
		redir = cmd->out_redir;
	else
		redir = cmd->in_redir;
	if (!redir)
		return ;
	while (redir->next)
		redir = redir->next;
	redir->fd = fd;
}
