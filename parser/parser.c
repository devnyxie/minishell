/* ************************************************************************** */
/*                                                                            */
/*                                   		               :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:59:16 by tafanasi          #+#    #+#             */
/*   Updated: 2025/07/17 11:55:45 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" // for t_shell and env access
#include "parser.h"

// Helper: Get env value by key
char	*get_env_value(char **envp, const char *key)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = strlen(key);
	while (envp[i])
	{
		if (strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return (envp[i] + key_len + 1);
		i++;
	}
	return ("");
}

void	handle_char(t_shell *shell)
{
	char	**input;

	input = &shell->parsed_input->input;
	if (**input == '>' || **input == '<')
		handle_redirect(shell->parsed_input);
	else if (**input == '|')
	{
		if (shell->parsed_input->first_cmd == NULL)
		{
			report_error(NULL, "syntax error near unexpected token `|'", 0);
			shell->parsed_input->is_valid = 0;
			return ;
		}
		if (**input)
			(*input)++; /* increment the character pointer */
	}
	else if (is_space(**input) && **input)
		(*input)++;
	else
		handle_cmd(shell->parsed_input);
}

void	parser(t_shell *shell, char *input)
{
	t_shell_input	*shell_input;

	shell_input = init_shell_input(input);
	shell->parsed_input = shell_input;
	// Expand variables once at the beginning
	handle_expand_variables(shell->envp, shell_input);
	while (*(shell_input->input) && shell_input->is_valid)
		handle_char(shell);
	if (!shell_input->first_cmd)
		shell_input->is_valid = 0;
	if (!shell_input->is_valid)
	{
		free_shell_input(shell_input);
		shell->parsed_input = NULL;
	}
}
