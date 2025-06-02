/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:59:16 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/02 12:54:17 by tafanasi         ###   ########.fr       */
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
	shell_input->input = input;
	return (shell_input);
}

/*
Is called for each byte, but the inner functions may move
the pointer of the input string for faster execution.
*/
void	handle_input(t_shell_input *shell_input)
{
	if (*(shell_input->input) == '>' || *(shell_input->input) == '<')
	{
		custom_error("Redirects are not implemented yet");
		if (*(shell_input->input))
			shell_input->input++;
	}
	else if (*(shell_input->input) == '|')
	{
		if (!shell_input->last_cmd)
			custom_error("syntax error near unexpected token `|'");
		custom_error("Pipes are not implemented yet");
		if (*(shell_input->input))
			shell_input->input++;
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