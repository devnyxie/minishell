/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:40:49 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/22 16:31:15 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

char	*expand_variable_in_quotes(char **input, char **envp, t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	char	*special_result;
	int		var_len;

	(*input)++;
	var_name = get_variable_name(input, &var_len);
	if (!var_name)
	{
		if (var_len == 0)
			return (ft_strdup("$"));
		return (ft_strdup("${}"));
	}
	special_result = handle_special_variable(var_name, shell, input, var_len);
	if (special_result)
		return (special_result);
	var_value = get_env_value(envp, var_name);
	*input += var_len;
	free(var_name);
	if (!var_value)
		return (ft_strdup(""));
	return (ft_strdup(var_value));
}

char	*grab_single_quoted_word(char **input)
{
	char	*start;
	char	*end;
	char	*result;

	if (**input != '\'')
		return (NULL);
	(*input)++;
	start = *input;
	end = start;
	while (*end && *end != '\'')
		end++;
	if (*end != '\'')
		return (NULL);
	result = ft_strndup(start, end - start);
	*input = end + 1;
	return (result);
}

char	*grab_quoted_word(char **input, char **envp, t_shell *shell)
{
	char	*start;
	char	*end;
	char	*content;
	char	*result;

	if (**input != '"')
		return (NULL);
	(*input)++;
	start = *input;
	end = find_quote_end(start);
	if (*end != '"')
		return (NULL);
	content = ft_strndup(start, end - start);
	if (!content)
		return (NULL);
	result = process_quoted_content(content, envp, shell);
	free(content);
	*input = end + 1;
	return (result);
}

int	has_unclosed_quotes(char *input)
{
	int	in_double_quotes;
	int	in_single_quotes;

	in_double_quotes = 0;
	in_single_quotes = 0;
	while (*input)
	{
		if (*input == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (*input == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (*input == '\\' && *(input + 1) && in_double_quotes)
			input++;
		input++;
	}
	return (in_double_quotes || in_single_quotes);
}
