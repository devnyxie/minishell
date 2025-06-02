/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:02:54 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/06/02 12:54:37 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
int	builtin_cd(char **args, char **envp[])
{
	char	*path;
	char	*old_pwd;
	char	cwd[PATH_MAX];

	//get current diretory before changing
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd: getcwd");
		return (1);
	}
	// determine target directory
	if (args[1] == NULL)
	{
		// nor arg: got to HOME
		path = getenv("HOME");
		if (!path)
		{
			write(2, "cd: HOME not set", ft_strlen("cd: HOME not set"));
			return (1);
		}
	}
	else if (args[2] != NULL)
	{
		// too many args
		write(2, "cd: HOME not set", ft_strlen("cd: HOME not set"));
		return (1);
	}
	else
		path = args[1];
	// change directory
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
}*/