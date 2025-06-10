/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:03:45 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/06/10 17:47:18 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(char **args)
{
	char cwd[PATH_MAX];

	// check for unwanted args
	if (args[1] != NULL)
	{
		exit(1);
	}
	// get the current working directory
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("pwd");
		exit(1);
	}
	printf("%s\n", cwd);
	return (0);
}