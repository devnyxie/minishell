/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:00:00 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/25 12:00:00 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_continuation(t_shell *shell, char *input)
{
	char	*continuation_input;
	char	*complete_input;

	continuation_input = readline("> ");
	if (!continuation_input)
	{
		free(input);
		clear_history();
		free_shell(shell);
		exit(EXIT_SUCCESS);
	}
	complete_input = malloc(strlen(input) + strlen(continuation_input) + 2);
	if (!complete_input)
		return (input);
	strcpy(complete_input, input);
	strcat(complete_input, " ");
	strcat(complete_input, continuation_input);
	free(input);
	free(continuation_input);
	return (complete_input);
}

char	*process_continuation(t_shell *shell, char *input)
{
	while (shell->parsed_input && shell->parsed_input->is_valid
		&& shell->parsed_input->incomplete_pipe)
	{
		input = handle_continuation(shell, input);
		if (shell->parsed_input)
		{
			free_shell_input(shell->parsed_input);
			shell->parsed_input = NULL;
		}
		parser(shell, input);
	}
	return (input);
}

void	process_input(t_shell *shell, char *input, char **args)
{
	if (input[0] != '\0')
		add_history(input);
	parser(shell, input);
	input = process_continuation(shell, input);
	if (shell->parsed_input && shell->parsed_input->is_valid)
		exec_cmd(shell->parsed_input->first_cmd, shell, args);
	if (shell->parsed_input)
	{
		free_shell_input(shell->parsed_input);
		shell->parsed_input = NULL;
	}
}
