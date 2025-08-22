/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:21:39 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/22 16:05:56 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

int	is_escaped_char(char c)
{
	return (c == '"' || c == '\\' || c == '$' || c == '`');
}

char	handle_escape_in_quotes(char **input)
{
	char	escaped_char;

	(*input)++;
	escaped_char = **input;
	if (is_escaped_char(escaped_char))
	{
		(*input)++;
		return (escaped_char);
	}
	return ('\\');
}

int	find_var_end(char *input)
{
	int	len;

	len = 0;
	if (input[0] == '{')
	{
		len = 1;
		while (input[len] && input[len] != '}')
			len++;
		if (input[len] == '}')
			len++;
	}
	else if (input[0] == '?')
		len = 1;
	else
	{
		while (input[len] && (ft_isalnum(input[len]) || input[len] == '_'))
			len++;
	}
	return (len);
}

size_t	calculate_quoted_length(char *input, char **envp,
		t_shell *shell)
{
	size_t	len;
	char	*temp_input;
	char	*var_value;

	len = 0;
	temp_input = input;
	while (*temp_input && *temp_input != '"')
	{
		if (*temp_input == '\\')
		{
			if (is_escaped_char(*(temp_input + 1)))
			{
				len++;
				temp_input += 2;
			}
			else
			{
				len += 2;
				temp_input++;
			}
		}
		else if (*temp_input == '$')
		{
			var_value = expand_variable_in_quotes(&temp_input, envp, shell);
			len += ft_strlen(var_value);
			free(var_value);
		}
		else
		{
			len++;
			temp_input++;
		}
	}
	return (len);
}
