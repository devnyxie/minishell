/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:00:00 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/25 12:31:37 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

char	*get_next_token_part(char **input, char **envp, t_shell *shell)
{
	if (**input == '\"')
		return (grab_quoted_word(input, envp, shell));
	else if (**input == '\'')
		return (grab_single_quoted_word(input));
	else
		return (grab_unquoted_word(input, envp, shell));
}

char	*join_and_free(char *result, char *part)
{
	char	*temp;

	temp = ft_strjoin(result, part);
	free(result);
	free(part);
	return (temp);
}
