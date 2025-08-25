/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:00:00 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/25 12:00:00 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

int	process_exit_code_length(t_shell *shell)
{
	if (shell)
		return (ft_strlen(ft_itoa(shell->exit_code)));
	else
		return (1);
}

int	process_variable_length(char *word, int *i, char **envp)
{
	int		var_len;
	char	*var_name;
	int		result_len;

	(*i)++;
	var_len = 0;
	while (word[*i + var_len] && (ft_isalnum(word[*i + var_len])
			|| word[*i + var_len] == '_'))
		var_len++;
	var_name = ft_strndup(&word[*i], var_len);
	result_len = ft_strlen(get_env_value(envp, var_name));
	free(var_name);
	*i += var_len;
	return (result_len);
}

int	calculate_expanded_length(char *word, char **envp, t_shell *shell)
{
	int		result_len;
	int		i;

	result_len = 0;
	i = 0;
	while (word[i])
	{
		if (word[i] == '$' && word[i + 1] == '?')
		{
			result_len += process_exit_code_length(shell);
			i += 2;
		}
		else if (word[i] == '$' && (ft_isalpha(word[i + 1])
				|| word[i + 1] == '_'))
			result_len += process_variable_length(word, &i, envp);
		else
		{
			result_len++;
			i++;
		}
	}
	return (result_len);
}
