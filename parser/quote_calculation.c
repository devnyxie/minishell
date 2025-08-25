/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_calculation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:00:00 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/25 12:00:00 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

size_t	handle_escape_length(char **temp_input)
{
	if (is_escaped_char(*((*temp_input) + 1)))
	{
		*temp_input += 2;
		return (1);
	}
	else
	{
		(*temp_input)++;
		return (2);
	}
}

size_t	handle_variable_length(char **temp_input, char **envp, t_shell *shell)
{
	char	*var_value;
	size_t	var_len;

	var_value = expand_variable_in_quotes(temp_input, envp, shell);
	var_len = ft_strlen(var_value);
	free(var_value);
	return (var_len);
}

size_t	calculate_quoted_length(char *input, char **envp, t_shell *shell)
{
	size_t	len;
	char	*temp_input;

	len = 0;
	temp_input = input;
	while (*temp_input && *temp_input != '"')
	{
		if (*temp_input == '\\')
			len += handle_escape_length(&temp_input);
		else if (*temp_input == '$')
			len += handle_variable_length(&temp_input, envp, shell);
		else
		{
			len++;
			temp_input++;
		}
	}
	return (len);
}
