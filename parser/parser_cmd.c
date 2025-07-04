/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:27:34 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/04 15:09:58 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_cmd	*init_cmd(char *cmd_name)
{
	t_cmd	*cmd;

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

static void	handle_args(t_cmd *cmd, t_shell_input *shell_input, char *cmd_name)
{
	int		arg_count;
	char	*arg;

	arg_count = 0;
	cmd->args = malloc(sizeof(char *) * 256);
	if (!cmd->args)
		return ;
	cmd->args[arg_count++] = cmd_name;
	while (*(shell_input->input) && *(shell_input->input) != '>'
		&& *(shell_input->input) != '<' && *(shell_input->input) != '|')
	{
		arg = grab_word(&(shell_input->input));
		if (!arg)
			break ;
		cmd->args[arg_count++] = arg;
	}
	cmd->args[arg_count] = NULL;
}

void append_to_linked_list(t_shell_input *shell_input, t_cmd *cmd)
{
	t_cmd *last_cmd;

	if (!shell_input->first_cmd)
	{
		shell_input->first_cmd = cmd;
		shell_input->last_cmd = cmd;
		return ;
	}
	last_cmd = shell_input->first_cmd;
	while(last_cmd->next != NULL)
		last_cmd = last_cmd->next;
	cmd->prev = last_cmd; // !!!
	last_cmd->next = cmd;
	shell_input->last_cmd = cmd;
	shell_input->cmds_count++;
}


void	handle_cmd(t_shell_input *shell_input )
{
	t_cmd	*cmd;
	char	*cmd_name;

	cmd_name = grab_word(&(shell_input->input));
	if (!cmd_name)
		return ;
	cmd = init_cmd(cmd_name);
	handle_args(cmd, shell_input, cmd_name);
	append_to_linked_list(shell_input, cmd);
}
