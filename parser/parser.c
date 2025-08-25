/* ************************************************************************** */
/*                                                                            */
/*                                   						:::      :::::::: */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 09:21:58 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/25 09:22:17 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

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
			(*input)++;
		shell->parsed_input->incomplete_pipe = 1;
	}
	else if (is_space(**input) && **input)
		(*input)++;
	else
		handle_cmd(shell->parsed_input, shell->envp, shell);
}

void	parser(t_shell *shell, char *input)
{
	t_shell_input	*shell_input;

	shell_input = init_shell_input(input);
	shell->parsed_input = shell_input;
	if (has_unclosed_quotes(input))
	{
		report_error(NULL, "syntax error: unclosed quotes", 0);
		shell_input->is_valid = 0;
		free_shell_input(shell_input);
		shell->parsed_input = NULL;
		return ;
	}
	while (*(shell_input->input) && shell_input->is_valid)
		handle_char(shell);
	if (!shell_input->first_cmd)
		shell_input->is_valid = 0;
	if (!shell_input->is_valid && !shell_input->incomplete_pipe)
	{
		free_shell_input(shell_input);
		shell->parsed_input = NULL;
	}
}
