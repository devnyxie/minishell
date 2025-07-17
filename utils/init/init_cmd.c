/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 02:28:29 by tafanasi          #+#    #+#             */
/*   Updated: 2025/07/17 02:40:36 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*init_cmd(char *cmd_name)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->name = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->pipe_read = -1;
	cmd->in_redir = NULL;
	cmd->out_redir = NULL;
	cmd->args = NULL;
	cmd->name = cmd_name;
	return (cmd);
}