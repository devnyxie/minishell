/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:59:58 by tafanasi          #+#    #+#             */
/*   Updated: 2025/05/29 15:29:49 by mmitkovi         ###   ########.fr       */
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
	char	*input;
	char 	**args = malloc(2 * sizeof(char *));
	if (!args)
	{
		custom_error("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	args[0] = NULL;
	args[1] = NULL;
	while (1)
	{
		input = readline("minishell$ ");
		if (input)
		{
			lexer(input, args);
			free(input);
		}
	}
}

int	main(void)
{
	setup_signals();
	await_input();
	return (0);
}
