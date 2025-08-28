/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_store.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:00:00 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/28 17:00:00 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

static void	add_to_redir_list(t_redirect **head, t_redirect *redir)
{
	t_redirect	*cur;

	if (!*head)
		*head = redir;
	else
	{
		cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = redir;
	}
}

void	handle_redirect_no_cmd(t_shell_input *shell_input,
	t_redirect_data *data)
{
	t_redirect	*redir;
	t_redirect	**head;

	if (data->fd != -1)
		redir = new_redirect_node_with_fd(data->type, data->name, data->fd);
	else
		redir = new_redirect_node(data->type, data->name);
	if (!redir)
	{
		shell_input->is_valid = 0;
		return ;
	}
	if (data->type == HEREDOC)
		redir->expand = data->expand;
	if (data->type == REDIR_IN || data->type == HEREDOC)
		head = &shell_input->pending_in_redir;
	else
		head = &shell_input->pending_out_redir;
	add_to_redir_list(head, redir);
}

static void	set_redir_fd(t_redirect *redir, int fd)
{
	while (redir->next)
		redir = redir->next;
	redir->fd = fd;
}

void	handle_redirect_with_cmd(t_redirect_data *data,
	t_shell_input *shell_input)
{
	t_redirect_info	info;
	t_redirect		*redir;

	info = (t_redirect_info){data->name, data->type, data->expand,
		data->cmd, shell_input};
	create_and_add_redirect(&info);
	if (data->fd != -1 && data->cmd->out_redir)
	{
		redir = data->cmd->out_redir;
		set_redir_fd(redir, data->fd);
	}
	else if (data->fd != -1 && data->cmd->in_redir)
	{
		redir = data->cmd->in_redir;
		set_redir_fd(redir, data->fd);
	}
}
