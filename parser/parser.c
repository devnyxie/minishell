/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:59:16 by tafanasi          #+#    #+#             */
/*   Updated: 2025/05/29 18:46:27 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

t_shell_input	*init_shell_input(char *input)
{
	t_shell_input	*shell_input;

	shell_input = malloc(sizeof(t_shell_input));
	if (!shell_input)
	{
		// TODO: err msg, mem handle
		return (NULL);
	}
	shell_input->first_cmd = NULL;
	shell_input->last_cmd = NULL;
	shell_input->is_valid = 1;
	shell_input->input = input;
	// shell_input->input = malloc((ft_strlen(input) + 1) * sizeof(char));
	// ft_strcpy(shell_input->input, input);
	return (shell_input);
}

int	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
	{
		return (c);
	}
	return (0);
}

void	skip_whitespace(char **input)
{
	while (is_space(**input))
		(*input)++;
}

char	*grab_word(char **input)
{
	char	*start;
	int		bytes;
	char	*word;
	int		j;

	bytes = 0;
	j = 0;
	skip_whitespace(input);
	start = *(input);
	while (start[bytes] && !is_space(start[bytes]) && start[bytes] != '>'
		&& start[bytes] != '<' && start[bytes] != '|')
		bytes++;
	word = malloc(bytes + 1);
	if (!word)
		return (NULL);
	while (j < bytes)
	{
		word[j] = start[j];
		j++;
	}
	word[bytes] = '\0';
	*(input) += bytes;
	return (word);
}

/*
Is called for each byte, but the inner functions may move
the pointer of the input string for faster execution.
*/
void	handle_input(t_shell_input *shell_input)
{
	char	*word;
	int		arg_count;
	char	*arg;
	t_cmd	*command;

	if (*(shell_input->input) == '>' || *(shell_input->input) == '<')
	{
		custom_error("Redirects are not implemented yet");
		if (*(shell_input->input))
			shell_input->input++;
		// grab_word doesn't even return the "> < |"
		// while (start[bytes] && !is_space(start[bytes]) && start[bytes] != '>'
		// && start[bytes] != '<' && start[bytes] != '|')
	}
	else if (*(shell_input->input) == '|')
	{
		if (!shell_input->last_cmd)
			custom_error("syntax error near unexpected token `|'");
		custom_error("Pipes are not implemented yet");
		if (*(shell_input->input))
		{
			shell_input->input++;
		}
		else
		{
			printf("Could not increment the input value: Pipe Issue\n");
			exit(1);
		}
	}
	else if (is_space(*(shell_input->input)))
	{
		if (*(shell_input->input))
			shell_input->input++;
	}
	else
	{
		word = grab_word(&(shell_input->input));
		if (!word)
			return ;
		command = malloc(sizeof(t_cmd));
		command->name = NULL;
		command->next = NULL;
		command->in_redir = NULL;
		command->out_redir = NULL;
		command->args = NULL;
		command->name = word;
		command->args = malloc(sizeof(char *) * 256);
		if (!command->args)
			return ;
		arg_count = 0;
		command->args[arg_count++] = word;
		skip_whitespace(&(shell_input->input));
		while (*(shell_input->input) && !is_space(*(shell_input->input))
			&& *(shell_input->input) != '>' && *(shell_input->input) != '<'
			&& *(shell_input->input) != '|')
		{
			arg = grab_word(&(shell_input->input));
			if (!arg)
				break ;
			command->args[arg_count++] = arg;
			skip_whitespace(&(shell_input->input));
		}
		command->args[arg_count] = NULL;
		// update the main struct
		if (!shell_input->first_cmd)
			shell_input->first_cmd = command;
		else
		{
			shell_input->last_cmd = command;
		}
		// === TESTING ===
		printf("Parsed command:\n");
		printf("  Name: %s\n", command->name);
		printf("  Args:");
		for (int i = 0; command->args[i]; i++)
		{
			printf(" \"%s\"", command->args[i]);
		}
		printf("\n");
		// === END ===
	}
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