/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:59:58 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/03 17:45:38 by tafanasi         ###   ########.fr       */
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

void	await_input(t_shell *shell)
{
	char			*input;
	t_cmd			*current_cmd;

	while (1)
	{
		input = readline("minishell$ ");
		if (input)
		{
			shell->parsed_input = parser(input);
			if (!shell->parsed_input)
				custom_error("Parser failed\n");
			current_cmd = shell->parsed_input->first_cmd;
			while (current_cmd)
			{
				lexer(current_cmd->name, current_cmd->args);
				current_cmd = current_cmd->next;
			}
		}
		free_shell_input(shell->parsed_input);
	}
	
}

int	main(void)
{
	t_shell	*shell;
	shell = init_shell();
	setup_signals();
	await_input(shell);
	return (0);
}
