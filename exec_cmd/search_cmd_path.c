/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:08:59 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/16 21:44:33 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"

char	*search_cmd_path(char *path, char *cmd)
{
	char	**paths;
	char	*full_path;
	char	*tmp;
	int		i;

	if (!path)
		return (NULL);
	i = 0;
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
		{
			free_2d(paths);
			return (NULL);
		}
		tmp = ft_strjoin(full_path, cmd);
		free(full_path);
		if (!tmp)
		{
			free_2d(paths);
			return (NULL);
		}
		if (access(tmp, X_OK) == 0)
		{
			free_2d(paths);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	free_2d(paths);
	return (NULL);
}
