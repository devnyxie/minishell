/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:59:58 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/10 13:35:50 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>

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
	char	*input;
	t_cmd *current_cmd;
	while (1)
	{
		input = readline("minishell$ ");
		if (input)
		{
			add_history(input);
			shell->parsed_input = parser(input);
			printf("=== Parsed commands ===\n");
			current_cmd = shell->parsed_input->first_cmd;
			while(current_cmd != NULL) {
				printf("  Name: %s,", current_cmd->name);
				printf("  Args:");
				for (int i = 0; current_cmd->args[i]; i++)
				{
					printf(" \"%s\"", current_cmd->args[i]);
				}
				current_cmd = current_cmd->next;
			}
			printf("\n=======================\n");
			if (shell->parsed_input->first_cmd != NULL)
				lexer(shell, shell->parsed_input->first_cmd);
		}
		free_shell_input(shell->parsed_input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	if (argc > 1 || argv[1])
		custom_error("Arguments are not supported");
	shell = init_shell(envp);
	setup_signals();
	await_input(shell);
	return (0);
}
