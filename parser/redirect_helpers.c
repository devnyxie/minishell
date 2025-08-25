/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:00:00 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/25 12:00:00 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

t_cmd	*create_empty_cmd(t_shell_input *shell_input)
{
	t_cmd	*cmd;

	cmd = init_cmd(NULL);
	if (!cmd)
	{
		shell_input->is_valid = 0;
		return (NULL);
	}
	cmd->args = malloc(sizeof(char *) * 2);
	if (!cmd->args)
	{
		free(cmd);
		shell_input->is_valid = 0;
		return (NULL);
	}
	cmd->args[0] = NULL;
	cmd->args[1] = NULL;
	append_to_linked_list(shell_input, cmd);
	return (cmd);
}

int	validate_redirect_name(char *name, t_shell_input *shell_input)
{
	if (!name || name[0] == '\0')
	{
		report_error(NULL, "syntax error near unexpected token `newline'", 0);
		shell_input->is_valid = 0;
		return (0);
	}
	return (1);
}

void	create_and_add_redirect(t_redirect_info *info)
{
	t_redirect	*redir;

	redir = new_redirect_node(info->type, info->name);
	if (!redir)
	{
		info->shell_input->is_valid = 0;
		return ;
	}
	if (info->type == HEREDOC)
		redir->expand = info->expand;
	add_redirect_to_cmd(info->cmd, redir);
}
