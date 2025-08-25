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
