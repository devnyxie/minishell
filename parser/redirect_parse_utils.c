/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parse_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:00:00 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/28 17:00:00 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

char	*grab_filename_or_delim(char **p, int is_hd, int *expand)
{
	char	*tok;

	if (!p || !*p)
		return (NULL);
	if (is_hd && (**p == '\'' || **p == '"'))
	{
		tok = read_quoted_str(p);
		if (!tok)
			return (NULL);
		if (expand)
			*expand = 0;
		return (tok);
	}
	tok = grab_word(p);
	if (!tok)
		return (NULL);
	if (expand)
	{
		if (is_hd)
			*expand = 1;
		else
			*expand = 0;
	}
	return (tok);
}

int	parse_fd_number(char **p)
{
	int	fd;
	int	i;

	if (!*p || !**p || !ft_isdigit(**p))
		return (-1);
	fd = 0;
	i = 0;
	while ((*p)[i] && ft_isdigit((*p)[i]))
	{
		fd = fd * 10 + ((*p)[i] - '0');
		i++;
	}
	if (!(*p)[i] || ((*p)[i] != '>' && (*p)[i] != '<'))
		return (-1);
	*p += i;
	return (fd);
}

static t_redirect_type	get_redirect_type_basic(char *p, int *consumed)
{
	t_redirect_type	type;

	if (*p == '>' && *(p + 1) == '>')
	{
		type = REDIR_APPEND;
		*consumed = 2;
	}
	else if (*p == '<' && *(p + 1) == '<')
	{
		type = HEREDOC;
		*consumed = 2;
	}
	else if (*p == '>')
	{
		type = REDIR_OUT;
		*consumed = 1;
	}
	else if (*p == '<')
	{
		type = REDIR_IN;
		*consumed = 1;
	}
	else
		return (REDIR_NONE);
	return (type);
}

t_redirect_type	get_redirect_type_with_fd(char *p, int *consumed)
{
	*consumed = 0;
	return (get_redirect_type_basic(p, consumed));
}
