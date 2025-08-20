/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:08:59 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/20 16:58:18 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"

static int	_has_slash(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static int	_is_executable(const char *p)
{
	if (p == NULL)
		return (0);
	if (access(p, X_OK) == 0)
		return (1);
	return (0);
}

static char	*_join_dir_cmd(const char *dir, const char *cmd)
{
	size_t	dd;
	size_t	cc;
	char	*out;

	if (dir == NULL || cmd == NULL)
		return (NULL);
	dd = ft_strlen(dir);
	cc = ft_strlen(cmd);
	out = (char *)malloc(dd + 1 + cc + 1);
	if (out == NULL)
		return (NULL);
	ft_memcpy(out, dir, dd);
	out[dd] = '/';
	ft_memcpy(out + dd + 1, cmd, cc);
	out[dd + 1 + cc] = '\0';
	return (out);
}

static char	*_probe_in_dirs(char **dirs, const char *cmd)
{
	size_t	i;
	char	*tmp;

	if (dirs == NULL || cmd == NULL)
		return (NULL);
	i = 0;
	while (dirs[i] != NULL)
	{
		tmp = _join_dir_cmd(dirs[i], cmd);
		if (tmp == NULL)
			return (NULL);
		if (_is_executable(tmp))
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

char	*search_cmd_path(char *path, char *cmd)
{
	char	**dirs;
	char	*res;

	if (cmd == NULL || cmd[0] == '\0')
		return (NULL);
	if (_has_slash(cmd))
	{
		if (_is_executable(cmd))
			return (ft_strdup(cmd));
		return (NULL);
	}
	if (path == NULL || path[0] == '\0')
		return (NULL);
	dirs = ft_split(path, ':');
	if (dirs == NULL)
		return (NULL);
	res = _probe_in_dirs(dirs, cmd);
	free_2d(dirs);
	return (res);
}
