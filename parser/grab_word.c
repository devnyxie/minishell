/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:48:15 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/22 15:12:45 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

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
