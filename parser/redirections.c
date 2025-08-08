/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:29:09 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/08 11:30:37 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

static t_redirect	*new_redirect_node(t_redirect_type type, char *file)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = file;
	redir->next = NULL;
	return (redir);
}

static void	add_redirect_to_cmd(t_cmd *cmd, t_redirect *redir)
{
	if (redir->type == REDIR_IN || redir->type == HEREDOC)
	{
		redir->next = cmd->in_redir;
		cmd->in_redir = redir;
	}
	else
	{
		redir->next = cmd->out_redir;
		cmd->out_redir = redir;
	}
}

t_redirect_type	redirect_type(t_shell_input *shell_input, t_cmd *cmd)
{
	t_redirect_type	type;

	cmd = shell_input->last_cmd;
	if (!cmd)
	{
		shell_input->input++;
		return (0);
	}
	if (*(shell_input->input) == '>' && *(shell_input->input + 1) == '>')
		type = REDIR_APPEND;
	else if (*(shell_input->input) == '<' && *(shell_input->input + 1) == '<')
		type = HEREDOC;
	else if (*(shell_input->input) == '>')
		type = REDIR_OUT;
	else if (*(shell_input->input) == '<')
		type = REDIR_IN;
	else
		return (0);
	if (type == REDIR_APPEND || type == HEREDOC)
		shell_input->input += 2;
	else if (type == REDIR_IN || type == REDIR_OUT)
		shell_input->input += 1;
	return (type);
}

void	handle_redirect(t_shell_input *shell_input)
{
	t_cmd			*current_cmd;
	t_redirect_type	type;
	char			*filename;
	t_redirect		*redir;

	current_cmd = shell_input->last_cmd;
	type = redirect_type(shell_input, current_cmd);
	skip_space(&shell_input->input);
	filename = grab_word(&shell_input->input);
	if (!filename)
	{
		report_error(NULL, "syntax error near unexpected token `newline'", 0);
		shell_input->is_valid = 0;
		return ;
	}
	redir = new_redirect_node(type, filename);
	if (!redir)
	{
		shell_input->is_valid = 0;
		return ;
	}
	add_redirect_to_cmd(current_cmd, redir);
}
