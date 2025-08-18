/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 02:28:29 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/14 15:26:26 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*init_cmd(char *cmd_name)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->name = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->pipe_read = -1;
	cmd->in_fd = -1;
	cmd->in_redir = NULL;
	cmd->out_redir = NULL;
	cmd->args = NULL;
	cmd->name = cmd_name;
	return (cmd);
}
