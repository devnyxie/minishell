/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:48:15 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/22 15:00:35 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

static char	*expand_unquoted_variables(char *word, char **envp, t_shell *shell)
{
	char	*result;
	char	*src;
	char	*dst;
	char	*var_name;
	char	*var_value;
	int		i;
	int		var_len;
	int		result_len;

	result_len = 0;
	i = 0;
	while (word[i])
	{
		if (word[i] == '$' && word[i + 1] == '?')
		{
			if (shell)
				result_len += ft_strlen(ft_itoa(shell->exit_code));
			else
				result_len += 1;
			i += 2;
		}
		else if (word[i] == '$' && (ft_isalpha(word[i + 1]) || word[i
				+ 1] == '_'))
		{
			i++;
			var_len = 0;
			while (word[i + var_len] && (ft_isalnum(word[i + var_len]) || word[i
					+ var_len] == '_'))
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
	result = malloc(result_len + 1);
	if (!result)
		return (word);
	src = word;
	dst = result;
	while (*src)
	{
		if (*src == '$' && *(src + 1) == '?')
		{
			src += 2;
			if (shell)
				var_value = ft_itoa(shell->exit_code);
			else
				var_value = ft_strdup("0");
			ft_strcpy(dst, var_value);
			dst += ft_strlen(var_value);
			free(var_value);
		}
		else if (*src == '$' && (ft_isalpha(*(src + 1)) || *(src + 1) == '_'))
		{
			src++;
			var_len = 0;
			while (src[var_len] && (ft_isalnum(src[var_len])
					|| src[var_len] == '_'))
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

static char	*grab_unquoted_word(char **input, char **envp, t_shell *shell)
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
	return (expand_unquoted_variables(word, envp, shell));
}

char	*grab_word(char **input)
{
	extern char	**environ;

	return (grab_word_with_env(input, environ, NULL));
}

char	*grab_word_with_env(char **input, char **envp, t_shell *shell)
{
	skip_space(input);
	if (!**input)
		return (NULL);
	if (**input == '\"')
		return (grab_quoted_word(input, envp, shell));
	if (**input == '\'')
		return (grab_single_quoted_word(input));
	return (grab_unquoted_word(input, envp, shell));
}
