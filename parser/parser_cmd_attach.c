/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_attach.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:00:00 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/28 17:00:00 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

static void	attach_redir_to_cmd(t_redirect **cmd_redir, t_redirect *pending)
{
	t_redirect	*cur;

	if (!*cmd_redir)
		*cmd_redir = pending;
	else
	{
		cur = *cmd_redir;
		while (cur->next)
			cur = cur->next;
		cur->next = pending;
	}
}

void	attach_pending_redirections(t_cmd *cmd, t_shell_input *shell_input)
{
	if (shell_input->pending_in_redir)
	{
		attach_redir_to_cmd(&cmd->in_redir, shell_input->pending_in_redir);
		shell_input->pending_in_redir = NULL;
	}
	if (shell_input->pending_out_redir)
	{
		attach_redir_to_cmd(&cmd->out_redir, shell_input->pending_out_redir);
		shell_input->pending_out_redir = NULL;
	}
}
