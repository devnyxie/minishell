/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:00:00 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/25 12:00:00 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

void	copy_exit_code(char **dst, t_shell *shell)
{
	char	*var_value;

	if (shell)
		var_value = ft_itoa(shell->exit_code);
	else
		var_value = ft_strdup("0");
	ft_strcpy(*dst, var_value);
	*dst += ft_strlen(var_value);
	free(var_value);
}

void	copy_env_variable(char **src, char **dst, char **envp)
{
	int		var_len;
	char	*var_name;
	char	*var_value;

	(*src)++;
	var_len = 0;
	while ((*src)[var_len] && (ft_isalnum((*src)[var_len])
			|| (*src)[var_len] == '_'))
		var_len++;
	var_name = ft_strndup(*src, var_len);
	var_value = get_env_value(envp, var_name);
	ft_strcpy(*dst, var_value);
	*dst += ft_strlen(var_value);
	free(var_name);
	*src += var_len;
}

char	*expand_unquoted_variables(char *word, char **envp, t_shell *shell)
{
	char	*result;
	char	*src;
	char	*dst;

	result = malloc(calculate_expanded_length(word, envp, shell) + 1);
	if (!result)
		return (word);
	src = word;
	dst = result;
	while (*src)
	{
		if (*src == '$' && *(src + 1) == '?')
		{
			src += 2;
			copy_exit_code(&dst, shell);
		}
		else if (*src == '$' && (ft_isalpha(*(src + 1)) || *(src + 1) == '_'))
			copy_env_variable(&src, &dst, envp);
		else
			*dst++ = *src++;
	}
	*dst = '\0';
	free(word);
	return (result);
}
