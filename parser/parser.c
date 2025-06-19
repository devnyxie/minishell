/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:59:16 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/10 11:54:16 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// TODO: err msg, mem handle
t_shell_input	*init_shell_input(char *input)
{
	t_shell_input	*shell_input;

	shell_input = malloc(sizeof(t_shell_input));
	if (!shell_input)
	{
		return (NULL);
	}
	shell_input->first_cmd = NULL;
	shell_input->last_cmd = NULL;
	shell_input->is_valid = 1;
	shell_input->cmds_count = 0;
	shell_input->input = input;
	return (shell_input);
}

static void	handle_redirect(t_shell_input *shell_input)
{
	t_cmd			*cmd;
	t_redirect		*redir;
	t_redirect_type	type;
	char			*file;

	cmd = shell_input->last_cmd;
	if (!cmd)
	{
		custom_error("syntax error: redirection with no command");
		shell_input->input++;
		return ;
	}
	// Determine redirection type
	if (*(shell_input->input) == '>' && *(shell_input->input + 1) == '>')
	{
		type = REDIR_APPEND;
		shell_input->input += 2;
	}
	else if (*(shell_input->input) == '<' && *(shell_input->input + 1) == '<')
	{
		type = HEREDOC;
		shell_input->input += 2;
	}
	else if (*(shell_input->input) == '>')
	{
		type = REDIR_OUT;
		shell_input->input += 1;
	}
	else if (*(shell_input->input) == '<')
	{
		type = REDIR_IN;
		shell_input->input += 1;
	}
	else
		return ;
	skip_space(&shell_input->input);
	file = grab_word(&shell_input->input);
	if (!file)
	{
		custom_error("syntax error: expected file after redirection");
		return ;
	}
	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return ;
	redir->type = type;
	redir->file = file;
	redir->next = NULL;
	// Attach to the correct list
	if (type == REDIR_IN || type == HEREDOC)
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

/*
Is called for each byte, but the inner functions may move
the pointer of the input string for faster execution.
*/
void	handle_input(t_shell_input *shell_input)
{
	if (*(shell_input->input) == '>' || *(shell_input->input) == '<')
	{
		handle_redirect(shell_input);
	}
	else if (*(shell_input->input) == '|')
	{
		if (shell_input->first_cmd == NULL)
			custom_error("syntax error near unexpected token `|'");
		// custom_error("Pipes are not implemented yet");
		if (*(shell_input->input))
			shell_input->input++;
		handle_cmd(shell_input);
	}
	else if (is_space(*(shell_input->input)))
	{
		if (*(shell_input->input))
			shell_input->input++;
	}
	else
		handle_cmd(shell_input);
}

/*
The loop will continue as long as the input pointer
is valid. Inner functions move the ptr of the input.
*/
t_shell_input	*parser(char *input)
{
	t_shell_input *shell_input = init_shell_input(input);
	while (*(shell_input->input))
		handle_input(shell_input);
	return (shell_input);
}