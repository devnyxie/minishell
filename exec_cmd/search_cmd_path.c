/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:08:59 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/10 16:46:46 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"

char	*search_cmd_path(char *path, char *cmd)
{
	char **paths;
	char *full_path;
	char *tmp;
	int i;

	i = 0;
	paths = ft_split(path, ':');
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
			break ;
		tmp = ft_strjoin(full_path, cmd);
		free(full_path);
		if (!tmp)
			break ;
		if (access(tmp, X_OK) == 0)
		{
			free_2d(paths);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}