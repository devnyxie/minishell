/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:48:15 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/02 12:48:32 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*grab_word(char **input)
{
	char	*start;
	int		bytes;
	char	*word;
	int		j;

	bytes = 0;
	j = 0;
	skip_space(input);
	start = *(input);
	while (start[bytes] && !is_space(start[bytes]) && start[bytes] != '>'
		&& start[bytes] != '<' && start[bytes] != '|')
		bytes++;
	word = malloc(bytes + 1);
	if (!word)
		return (NULL);
	while (j < bytes)
	{
		word[j] = start[j];
		j++;
	}
	word[bytes] = '\0';
	*(input) += bytes;
	return (word);
}