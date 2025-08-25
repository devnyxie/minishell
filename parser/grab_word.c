/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:48:15 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/25 12:31:37 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

char	*grab_unquoted_word(char **input, char **envp, t_shell *shell)
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

static char	*concatenate_tokens(char **input, char **envp, t_shell *shell)
{
	char	*result;
	char	*part;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (**input && !is_space(**input) && **input != '>' && **input != '<'
		&& **input != '|')
	{
		part = get_next_token_part(input, envp, shell);
		if (!part)
			break ;
		result = join_and_free(result, part);
		if (!result)
			return (NULL);
	}
	if (ft_strlen(result) == 0)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

char	*grab_word_with_env(char **input, char **envp, t_shell *shell)
{
	skip_space(input);
	if (!**input)
		return (NULL);
	return (concatenate_tokens(input, envp, shell));
}
