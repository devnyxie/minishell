/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:59:58 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/22 13:36:52 by tafanasi         ###   ########.fr       */
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
	signal(SIGQUIT, SIG_IGN);
}

void	await_input(t_shell *shell, char **args)
{
	char	*input;
	char	*continuation_input;
	char	*complete_input;

	while (1)
	{
		input = readline("minishell$ ");
		if (input)
		{
			if (input[0] != '\0')
				add_history(input);
			parser(shell, input);
			
			// Check for incomplete pipe and handle continuation
			while (shell->parsed_input && shell->parsed_input->is_valid && 
				   shell->parsed_input->incomplete_pipe)
			{
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
					break;
				strcpy(complete_input, input);
				strcat(complete_input, " ");
				strcat(complete_input, continuation_input);
				
				free(input);
				free(continuation_input);
				input = complete_input;
				
				if (shell->parsed_input)
				{
					free_shell_input(shell->parsed_input);
					shell->parsed_input = NULL;
				}
				parser(shell, input);
			}
			
			if (shell->parsed_input && shell->parsed_input->is_valid)
				exec_cmd(shell->parsed_input->first_cmd, shell, args);
			if (shell->parsed_input)
			{
				free_shell_input(shell->parsed_input);
				shell->parsed_input = NULL;
			}
			free(input);
		}
		else
		{
			clear_history();
			free_shell(shell);
			exit(EXIT_SUCCESS);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	if (argc > 1 || argv[0] == NULL)
		custom_error("Arguments are not supported");
	shell = init_shell(envp);
	setup_signals();
	await_input(shell, argv);
	return (0);
}
