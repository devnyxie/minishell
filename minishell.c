/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
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
	while (1)
	{
		input = readline("minishell$ ");
		if (input)
		{
			add_history(input);
			shell->parsed_input = parser(input);
			if (shell->parsed_input->first_cmd != NULL)
				exec_cmd(shell->parsed_input->first_cmd, shell);
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
