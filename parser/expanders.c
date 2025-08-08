/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:32:03 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/08 11:34:08 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

static int	find_end_of_var(char *input, int i)
{
	while (ft_isalnum(input[i]) || input[i] == '_')
		i++;
	return (i);
}

/* calculate the length of the string after variable expansion */
static size_t	calculate_expanded_len(char *input, char **envp)
{
	size_t	len;
	char	*var_name;
	int		i;
	int		var_start;

	len = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && (ft_isalpha(input[i + 1]) || input[i
					+ 1] == '_'))
		{
			var_start = ++i;
			i = find_end_of_var(input, i);
			var_name = ft_strndup(&input[var_start], i - var_start);
			len += ft_strlen(get_env_value(envp, var_name));
			free(var_name);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

/* build the new string with expanded variables */
static void	build_expanded_string(char *input, char *new_input, char **envp)
{
	int		i;
	int		j;
	int		var_start;
	char	*var_name;
	char	*var_value;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '$' && (ft_isalpha(input[i + 1]) || input[i
					+ 1] == '_'))
		{
			var_start = ++i;
			i = find_end_of_var(input, i);
			var_name = ft_strndup(&input[var_start], i - var_start);
			var_value = get_env_value(envp, var_name);
			ft_strcpy(&new_input[j], var_value);
			j += ft_strlen(var_value);
			free(var_name);
		}
		else
			new_input[j++] = input[i++];
	}
	new_input[j] = '\0';
}

void	handle_expand_variables(char **envp, t_shell_input *shell_input)
{
	char	*original_input;
	char	*new_input;
	int		final_len;

	original_input = shell_input->input;
	final_len = calculate_expanded_len(original_input, envp);
	if (final_len == ft_strlen(original_input))
		return ;
	new_input = malloc(sizeof(char) * (final_len + 1));
	if (!new_input)
		return ;
	build_expanded_string(original_input, new_input, envp);
	free(shell_input->input);
	shell_input->input = new_input;
}
