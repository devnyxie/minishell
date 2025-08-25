/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:00:00 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/25 12:00:00 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

char	*find_quote_end(char *start)
{
	char	*end;

	end = start;
	while (*end && *end != '"')
	{
		if (*end == '\\' && *(end + 1))
			end += 2;
		else
			end++;
	}
	return (end);
}

static void	copy_literal_char(char **dst, char **src)
{
	**dst = **src;
	(*dst)++;
	(*src)++;
}

static void	copy_expanded_var(char **dst, char **src, char **envp, t_shell *sh)
{
	char	*var_value;

	var_value = expand_variable_in_quotes(src, envp, sh);
	ft_strcpy(*dst, var_value);
	*dst += ft_strlen(var_value);
	free(var_value);
}

static void	process_char(char **src, char **dst, char **envp, t_shell *shell)
{
	if (**src == '\\' && (*((*src) + 1) == '"' || *((*src) + 1) == '\\'
			|| *((*src) + 1) == '$'))
	{
		(*src)++;
		copy_literal_char(dst, src);
	}
	else if (**src == '$')
		copy_expanded_var(dst, src, envp, shell);
	else
		copy_literal_char(dst, src);
}

char	*process_quoted_content(char *input, char **envp, t_shell *shell)
{
	size_t	final_len;
	char	*result;
	char	*src;
	char	*dst;

	final_len = calculate_quoted_length(input, envp, shell);
	result = malloc(final_len + 1);
	if (!result)
		return (NULL);
	src = input;
	dst = result;
	while (*src && *src != '"')
		process_char(&src, &dst, envp, shell);
	*dst = '\0';
	return (result);
}
