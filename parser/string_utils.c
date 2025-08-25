/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:00:00 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/25 12:00:00 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

int	str_len_inside_quotes(char **p, char q)
{
	int	len;

	len = 0;
	while (**p && **p != q)
	{
		(*p)++;
		len++;
	}
	return (len);
}

char	*allocate_and_copy(char *start, size_t len)
{
	char	*out;
	size_t	i;

	out = (char *)malloc(len + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (i < len)
		out[i++] = *start++;
	out[len] = '\0';
	return (out);
}

char	*read_quoted_str(char **p)
{
	char	q;
	char	*start;
	size_t	len;

	if (!p || !*p)
		return (NULL);
	q = **p;
	if (q != '\'' && q != '"')
		return (NULL);
	(*p)++;
	start = *p;
	len = str_len_inside_quotes(p, q);
	if (**p != q)
		return (NULL);
	(*p)++;
	return (allocate_and_copy(start, len));
}
