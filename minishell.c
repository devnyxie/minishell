/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:59:58 by tafanasi          #+#    #+#             */
/*   Updated: 2025/07/17 12:09:24 by tafanasi         ###   ########.fr       */
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

void	await_input(t_shell *shell, char **args)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (input)
		{
			if (input[0] != '\0')
				add_history(input);
			parser(shell, input);
			if (shell->parsed_input && shell->parsed_input->is_valid)
				exec_cmd(shell->parsed_input->first_cmd, shell, args);
			if (shell->parsed_input)
			{
				free_shell_input(shell->parsed_input);
				shell->parsed_input = NULL; // Set to NULL after freeing
			}
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
