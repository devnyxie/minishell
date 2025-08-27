/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:27:34 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/27 15:30:00 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	handle_cmd(t_shell_input *shell_input, char **envp, t_shell *shell)
{
	t_cmd			*cmd;
	char			*cmd_name;
	t_cmd_params	params;

	cmd_name = grab_word_with_env(&(shell_input->input), envp, shell);
	if (!cmd_name)
		return ;
	shell_input->incomplete_pipe = 0;
	if (check_and_handle_variable_assignment(cmd_name, shell))
	{
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
