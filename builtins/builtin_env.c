/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:30:13 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/26 17:58:06 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(t_shell *shell, char **args)
{
	int	i;

	if (args && args[1])
	{
		report_error(args[1], "No such file or directory", 0);
		exit(127);
	}
	if (!shell->envp)
		return (EXIT_FAILURE);
	i = 0;
	while (i < shell->env_count)
	{
		printf("%s\n", shell->envp[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
