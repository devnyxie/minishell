/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:59:58 by tafanasi          #+#    #+#             */
/*   Updated: 2025/05/29 15:56:02 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Clear the line, move to new line, show prompt
void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	printf("\n");
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN); // ignore Ctrl+"/"
}

void	await_input(void)
{
	char			*input;
	t_shell_input	*shell_input;
	t_cmd			*current_cmd;

	while (1)
	{
		input = readline("minishell$ ");
		if (input)
		{
			shell_input = parser(input);
			current_cmd = shell_input->first_cmd;
			while (current_cmd)
			{
				lexer(current_cmd->name, current_cmd->args);
				current_cmd = current_cmd->next;
			}
			free(input);
			free(shell_input);
		}
	}
}

int	main(void)
{
	setup_signals();
	await_input();
	return (0);
}
