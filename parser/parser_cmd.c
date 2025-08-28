/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:27:34 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/28 11:19:46 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

void	handle_cmd(t_shell_input *shell_input, char **envp, t_shell *shell)
{
	t_cmd			*cmd;
	char			*cmd_name;
	t_cmd_params	params;

	cmd_name = grab_word_with_env(&(shell_input->input), envp, shell);
	if (!cmd_name)
		return ;
	shell_input->incomplete_pipe = 0;
	if (is_variable_assignment(cmd_name))
	{
		handle_variable_assignment(cmd_name, shell);
		free(cmd_name);
		return ;
	}
	cmd = init_cmd(cmd_name);
	attach_pending_redirections(cmd, shell_input);
	params.shell_input = shell_input;
	params.envp = envp;
	params.shell = shell;
	handle_args(cmd, cmd_name, &params);
	append_to_linked_list(shell_input, cmd);
}
