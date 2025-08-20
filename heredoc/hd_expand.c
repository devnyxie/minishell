/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:30:38 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/20 15:03:45 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static size_t	var_span(const char *p)
{
	size_t	i;

	if (*p == '?')
		return (1);
	if (!(ft_isalpha((unsigned char)*p) || *p == '_'))
		return (0);
	i = 1;
	while (ft_isalnum((unsigned char)p[i]) || p[i] == '_')
		i++;
	return (i);
}

static int	write_var(int fd, const char *s, size_t n, t_shell *sh)
{
	char	*key;
	char	*val;

	if (n == 1 && *s == '?')
		return (hd_write_status(fd, sh->exit_code));
	key = ft_strndup(s, n);
	if (!key)
		return (-1);
	val = (char *)get_env_value(sh->envp, key);
	if (val)
	{
		if (hd_write_str(fd, val, ft_strlen(val)) < 0)
		{
			free(key);
			return (-1);
		}
	}
	free(key);
	return (0);
}

static int	process_dollar(t_hdctx *x)
{
	size_t	vlen;

	if (hd_write_str(x->fd, x->line + x->chunk, x->i - x->chunk) < 0)
		return (-1);
	x->i++;
	if (!x->line[x->i])
		return (hd_write_str(x->fd, "$", 1));
	vlen = var_span(x->line + x->i);
	if (vlen == 0)
	{
		if (hd_write_str(x->fd, "$", 1) < 0)
			return (-1);
	}
	else
	{
		if (write_var(x->fd, x->line + x->i, vlen, x->sh) < 0)
			return (-1);
		x->i += vlen;
	}
	x->chunk = x->i;
	return (0);
}

int	hd_write_expanded_line(int fd, const char *line, int expand, t_shell *sh)
{
	t_hdctx	x;

	if (!expand)
		return (hd_write_str(fd, line, ft_strlen(line)));
	x.fd = fd;
	x.line = line;
	x.i = 0;
	x.chunk = 0;
	x.sh = sh;
	while (line[x.i])
	{
		if (line[x.i] == '$')
		{
			if (process_dollar(&x) < 0)
				return (-1);
			continue ;
		}
		x.i++;
	}
	if (hd_write_str(fd, line + x.chunk, x.i - x.chunk) < 0)
		return (-1);
	return (0);
}
