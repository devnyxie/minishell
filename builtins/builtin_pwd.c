/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:03:45 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/05 12:45:14 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(char **args)
{
	char	cwd[PATH_MAX];

	if (args[1] != NULL)
		return (1);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		report_error(NULL, "pwd", 1);
		exit(1);
	}
	printf("%s\n", cwd);
	return (0);
}
