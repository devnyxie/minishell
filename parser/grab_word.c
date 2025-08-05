/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:48:15 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/05 18:06:54 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

// expands variables in unquoted content
static char	*expand_unquoted_variables(char *word, char **envp)
{
	char	*result;
	char	*src;
	char	*dst;
	char	*var_name;
	char	*var_value;
	int		i, var_len, result_len;
	
	result_len = 0;
	i = 0;
	while (word[i])
	{
		if (word[i] == '$' && (ft_isalpha(word[i + 1]) || word[i + 1] == '_'))
		{
			i++; // skip $
			var_len = 0;
			while (word[i + var_len] && (ft_isalnum(word[i + var_len]) || word[i + var_len] == '_'))
				var_len++;
			var_name = ft_strndup(&word[i], var_len);
			var_value = get_env_value(envp, var_name);
			result_len += ft_strlen(var_value);
			free(var_name);
			i += var_len;
		}
		else
		{
			result_len++;
			i++;
		}
	}
	
	// build result string
	// todo: optimize all this
	result = malloc(result_len + 1);
	if (!result)
		return (word);
	
	src = word;
	dst = result;
	while (*src)
	{
		if (*src == '$' && (ft_isalpha(*(src + 1)) || *(src + 1) == '_'))
		{
			src++; // skip $
			var_len = 0;
			while (src[var_len] && (ft_isalnum(src[var_len]) || src[var_len] == '_'))
				var_len++;
			var_name = ft_strndup(src, var_len);
			var_value = get_env_value(envp, var_name);
			ft_strcpy(dst, var_value);
			dst += ft_strlen(var_value);
			free(var_name);
			src += var_len;
		}
		else
		{
			*dst++ = *src++;
		}
	}
	*dst = '\0';
	
	free(word);
	return (result);
}

// grabs a regular word without quotes
static char	*grab_unquoted_word(char **input, char **envp)
{
	char	*start;
	int		bytes;
	char	*word;
	int		j;

	bytes = 0;
	j = 0;
	start = *input;
	while (start[bytes] && !is_space(start[bytes]) && start[bytes] != '>'
		&& start[bytes] != '<' && start[bytes] != '|' && start[bytes] != '"'
		&& start[bytes] != '\'')
		bytes++;
	if (bytes == 0)
		return (NULL);
	word = malloc((bytes + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (j < bytes)
	{
		word[j] = start[j];
		j++;
	}
	word[bytes] = '\0';
	*input += bytes;
	
	// continue exp in unquoted content func
	return (expand_unquoted_variables(word, envp));
}

char	*grab_word(char **input)
{
	extern char **environ;
	return (grab_word_with_env(input, environ));
}

char	*grab_word_with_env(char **input, char **envp)
{
	skip_space(input);
	if (!**input)
		return (NULL);
	
		return (grab_quoted_word(input, envp));

	if (**input == '\'')
		return (grab_single_quoted_word(input));
	
	// otherwise regular word
	return (grab_unquoted_word(input, envp));
}