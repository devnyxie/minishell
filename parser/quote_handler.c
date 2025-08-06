/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:40:49 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/05 17:59:39 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

/*
** is_escaped_char - checks if a character should be treated as escaped inside double quotes
** Only \", \\, \$, and \` are escaped inside double quotes in bash
*/
static int	is_escaped_char(char c)
{
	return (c == '"' || c == '\\' || c == '$' || c == '`');
}

/*
** handle_escape_in_quotes - processes escape sequences inside double quotes
** Returns the character to add to the result, advances input pointer
*/
static char	handle_escape_in_quotes(char **input)
{
	char	escaped_char;

	(*input)++; // skip the backslash
	escaped_char = **input;
	if (is_escaped_char(escaped_char))
	{
		(*input)++; // consume the escaped character
		return (escaped_char);
	}
	// If not a special escaped char, keep the backslash
	return ('\\');
}

/*
** find_var_end - finds the end of a variable name starting from current position
** Returns the length of the variable name
*/
static int	find_var_end(char *input)
{
	int	len;

	len = 0;
	if (input[0] == '{')
	{
		len = 1; // skip opening brace
		while (input[len] && input[len] != '}')
			len++;
		if (input[len] == '}')
			len++; // include closing brace
	}
	else
	{
		while (input[len] && (ft_isalnum(input[len]) || input[len] == '_'))
			len++;
	}
	return (len);
}

/*
** expand_variable_in_quotes - expands a single variable inside double quotes
** Returns the expanded value, advances input pointer
*/
static char	*expand_variable_in_quotes(char **input, char **envp)
{
	char	*var_name;
	char	*var_value;
	int		var_len;
	int		name_start;
	int		name_len;

	(*input)++; // skip the '$'
	var_len = find_var_end(*input);
	if (var_len == 0)
		return (ft_strdup("$")); // just a lone $
	
	// Handle ${VAR} format
	if (**input == '{')
	{
		name_start = 1;
		name_len = var_len - 2; // exclude braces
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
	
	var_value = get_env_value(envp, var_name);
	*input += var_len; // advance past the variable
	free(var_name);
	
	return (ft_strdup(var_value ? var_value : ""));
}

/*
** calculate_quoted_length - calculates the final length after processing quotes and expansions
*/
static size_t	calculate_quoted_length(char *input, char **envp)
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
				len++; // one character for the escaped char
				temp_input += 2;
			}
			else
			{
				len += 2; // backslash + following char
				temp_input++;
			}
		}
		else if (*temp_input == '$')
		{
			var_value = expand_variable_in_quotes(&temp_input, envp);
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

/*
** process_quoted_content - processes the content inside double quotes
** Handles escape sequences and variable expansion
*/
static char	*process_quoted_content(char *input, char **envp)
{
	size_t	final_len;
	char	*result;
	char	*result_ptr;
	char	*var_value;
	char	escaped_char;

	final_len = calculate_quoted_length(input, envp);
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
			var_value = expand_variable_in_quotes(&input, envp);
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

/*
** grab_single_quoted_word - extracts and processes content within single quotes
** Single quotes preserve everything literally (no variable expansion, no escapes)
** Returns the literal string, advances input pointer past closing quote
*/
char	*grab_single_quoted_word(char **input)
{
	char	*start;
	char	*end;
	char	*result;
	
	if (**input != '\'')
		return (NULL);
	
	(*input)++; // skip opening quote
	start = *input;
	
	// Find closing quote - no escaping in single quotes
	end = start;
	while (*end && *end != '\'')
		end++;
	
	if (*end != '\'')
	{
		// Unclosed quote - should probably return an error
		return (NULL);
	}
	
	// Extract content between quotes (literal)
	result = ft_strndup(start, end - start);
	
	// Advance input past closing quote
	*input = end + 1;
	
	return (result);
}

/*
** grab_quoted_word - extracts and processes content within double quotes
** Returns the processed string, advances input pointer past closing quote
*/
char	*grab_quoted_word(char **input, char **envp)
{
	char	*start;
	char	*end;
	char	*content;
	char	*result;
	
	if (**input != '"')
		return (NULL);
	
	(*input)++; // skip opening quote
	start = *input;
	
	// Find closing quote, handling escapes
	end = start;
	while (*end && *end != '"')
	{
		if (*end == '\\' && *(end + 1))
			end += 2; // skip escaped sequence
		else
			end++;
	}
	
	if (*end != '"')
	{
		// Unclosed quote - should probably return an error
		return (NULL);
	}
	
	// Extract content between quotes
	content = ft_strndup(start, end - start);
	if (!content)
		return (NULL);
	
	// Process the content (expand variables, handle escapes)
	result = process_quoted_content(content, envp);
	free(content);
	
	// Advance input past closing quote
	*input = end + 1;
	
	return (result);
}

/*
** has_unclosed_quotes - checks if the input has unclosed quotes (single or double)
** Returns 1 if quotes are unclosed, 0 otherwise
*/
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
			input++; // skip escaped character in double quotes only
		input++;
	}
	return (in_double_quotes || in_single_quotes);
}
