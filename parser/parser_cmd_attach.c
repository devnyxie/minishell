/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_attach.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:30:00 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/27 15:30:00 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	attach_input_redirections(t_cmd *cmd, t_shell_input *shell_input)
{
	t_redirect	*cur;

	if (shell_input->pending_in_redir)
	{
		if (!cmd->in_redir)
			cmd->in_redir = shell_input->pending_in_redir;
		else
		{
			cur = cmd->in_redir;
			while (cur->next)
				cur = cur->next;
			cur->next = shell_input->pending_in_redir;
		}
		shell_input->pending_in_redir = NULL;
	}
}

static void	attach_output_redirections(t_cmd *cmd, t_shell_input *shell_input)
{
	t_redirect	*cur;

	if (shell_input->pending_out_redir)
	{
		if (!cmd->out_redir)
			cmd->out_redir = shell_input->pending_out_redir;
		else
		{
			cur = cmd->out_redir;
			while (cur->next)
				cur = cur->next;
			cur->next = shell_input->pending_out_redir;
		}
		shell_input->pending_out_redir = NULL;
	}
}

void	attach_pending_redirections(t_cmd *cmd, t_shell_input *shell_input)
{
	attach_input_redirections(cmd, shell_input);
	attach_output_redirections(cmd, shell_input);
}

void	append_to_linked_list(t_shell_input *shell_input, t_cmd *cmd)
{
	t_cmd	*last_cmd;

	if (!shell_input->first_cmd)
	{
		shell_input->first_cmd = cmd;
		shell_input->last_cmd = cmd;
		return ;
	}
	last_cmd = shell_input->first_cmd;
	while (last_cmd->next != NULL)
		last_cmd = last_cmd->next;
	cmd->prev = last_cmd;
	last_cmd->next = cmd;
	shell_input->last_cmd = cmd;
	shell_input->cmds_count++;
}
