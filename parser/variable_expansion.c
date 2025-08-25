/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:00:00 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/25 12:00:00 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

char	*handle_special_variable(char *var_name, t_shell *shell,
		char **input, int var_len)
{
	int	name_len;

	name_len = ft_strlen(var_name);
	if (name_len == 1 && var_name[0] == '?')
	{
		*input += var_len;
		free(var_name);
		return (ft_itoa(shell->exit_code));
	}
	return (NULL);
}

char	*get_variable_name(char **input, int *var_len)
{
	int		name_start;
	int		name_len;

	*var_len = find_var_end(*input);
	if (*var_len == 0)
		return (NULL);
	if (**input == '{')
	{
		name_start = 1;
		name_len = *var_len - 2;
		if (name_len <= 0)
			return (NULL);
	}
	else
	{
		name_start = 0;
		name_len = *var_len;
	}
	return (ft_strndup(*input + name_start, name_len));
}
