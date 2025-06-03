/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:03:45 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/06/02 12:12:19 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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