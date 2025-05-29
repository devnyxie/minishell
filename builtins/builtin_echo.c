/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:27:57 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/05/29 12:21:13 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	i = 0;
	newline = 1;
	
	// check for -n
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i = 2; // start from next arg
	}

	// print arg separated by spaces
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	// add newline unless -n was specified
	if (newline)
		printf("\n");
	return (0);
}

int	builtin_pwd(char **args)
{
	char	cwd[PATH_MAX];

	// check for unwanted args
	if (args[1] != NULL)
	{
		return (1);
	}

	// get the current working directory
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("pwd");
		return (1);
	}

	printf("%s\n", cwd);
	return (0);
}

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
}