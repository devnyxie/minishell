/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:59:16 by tafanasi          #+#    #+#             */
/*   Updated: 2025/05/29 13:44:57 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

int	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
	{
		return (c);
	}
	return (0);
}

// @manipulates the "i"
void	skip_whitespace(char *input, int *i)
{
	printf("skip_whitespaces func\n");
	while (is_space(input[*i]))
	{
		(*i)++;
	}
}

char	*grab_word(char *input, int *i)
{
	int		start;
	int		bytes;
	char	*word;

	start = *i;
	bytes = 0;
	skip_whitespace(input, i);
	while (input[*i + bytes] && !is_space(input[*i + bytes]) && input[*i
		+ bytes] != '>' && input[*i + bytes] != '<' && input[*i + bytes] != '|')
		bytes++;
	// TODO: free later
	word = malloc((bytes + 1) * sizeof(char));
	if (!word)
		return (NULL);
	for (int j = 0; j < bytes; j++)
		word[j] = input[start + j];
	word[bytes] = '\0';
	*i += bytes;
	printf("grabbed word: %s\n", word);
	return (word);
}

void	handle_cmd(char *input, t_cmd *last_cmd, t_cmd *command, int *i)
{
	char	*word;
	int		arg_count;
	char	*arg;

	printf("handle_cmd function\n");
	word = grab_word(input, i);
	if (!word)
		return ;
	if (word[*i] == '>' || '<')
	{
		printf("Handling redirection...\n");
		// handle redirections
		// 1. >>, <<, >, <
		// 2. files
		// ...
	}
	else if (word[*i] == '|')
	{
		printf("Handling pipe...\n");
		// ...
		if (!last_cmd)
			custom_error("syntax error near unexpected token `|'");
		// re-run the handle_cmd command using "command" as "last_cmd"
	}
	else
	{
		printf("Parsing the command...\n");
		// handle the commmand
		// 1. cmd
		// 2. args
		command->name = word;
		arg_count = 0;
		command->args = malloc(sizeof(char *) * 256); // arbitrary max args
		if (!command->args)
			return ;
		command->args[arg_count++] = word;
		skip_whitespace(input, i);
		while (input[*i] && !is_space(input[*i]) && input[*i] != '>'
			&& input[*i] != '<' && input[*i] != '|')
		{
			arg = grab_word(input, i);
			if (!arg)
				break ;
			command->args[arg_count++] = arg;
			skip_whitespace(input, i);
		}
		command->args[arg_count] = NULL;
		printf("Finished the parsing of the command...\n");
		// the assign of parsed_input.cmds should be here
	}
}

/*
input is not manipulated in any of the functions
*/
int	parser(char *input)
{
	t_shell_input parsed_input;
	parsed_input.cmds = NULL;
	t_cmd *last_cmd = NULL;
	if (!parsed_input.cmds)
		return (1);
	parsed_input.is_valid = 1;
	int i;

	i = 0;
	while (input[i])
	{
		printf("main loop started\n");
		t_cmd *command = malloc(sizeof(t_cmd));
		handle_cmd(input, last_cmd, command, &i);
		// assign cmds without linking them
		// link occurs in pipe segment
		if (!parsed_input.cmds)
		{
			parsed_input.cmds = command;
			last_cmd = command;
		}
		else
		{
			last_cmd = command;
		}
	}
	return (0);
}