/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:40:49 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/22 14:56:57 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

static int	is_escaped_char(char c)
{
	return (c == '"' || c == '\\' || c == '$' || c == '`');
}

static char	handle_escape_in_quotes(char **input)
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

static int	find_var_end(char *input)
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

static char	*expand_variable_in_quotes(char **input, char **envp,
		t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	int		var_len;
	int		name_start;
	int		name_len;

	(*input)++;
	var_len = find_var_end(*input);
	if (var_len == 0)
		return (ft_strdup("$"));
	if (**input == '{')
	{
		name_start = 1;
		name_len = var_len - 2;
		if (name_len <= 0)
			return (ft_strdup("${}"));
	}
	else
	{
		name_start = 0;
		name_len = var_len;
	}
	var_name = ft_strndup(*input + name_start, name_len);
	if (!var_name)
		return (ft_strdup(""));
	if (name_len == 1 && var_name[0] == '?')
	{
		*input += var_len;
		free(var_name);
		return (ft_itoa(shell->exit_code));
	}
	var_value = get_env_value(envp, var_name);
	*input += var_len;
	free(var_name);
	return (ft_strdup(var_value ? var_value : ""));
}

static size_t	calculate_quoted_length(char *input, char **envp,
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

static char	*process_quoted_content(char *input, char **envp, t_shell *shell)
{
	size_t	final_len;
	char	*result;
	char	*result_ptr;
	char	*var_value;
	char	escaped_char;

	final_len = calculate_quoted_length(input, envp, shell);
	result = malloc(final_len + 1);
	if (!result)
		return (NULL);
	result_ptr = result;
	while (*input && *input != '"')
	{
		if (*input == '\\')
		{
			escaped_char = handle_escape_in_quotes(&input);
			*result_ptr++ = escaped_char;
		}
		else if (*input == '$')
		{
			var_value = expand_variable_in_quotes(&input, envp, shell);
			ft_strcpy(result_ptr, var_value);
			result_ptr += ft_strlen(var_value);
			free(var_value);
		}
		else
		{
			*result_ptr++ = *input++;
		}
	}
	*result_ptr = '\0';
	return (result);
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
	end = start;
	while (*end && *end != '"')
	{
		if (*end == '\\' && *(end + 1))
			end += 2;
		else
			end++;
	}
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
