/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:30:13 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/22 11:36:01 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(t_shell *shell, char **args)
{
	int	i;

	if (args && args[1])
	{
		report_error(args[0], "No such file or directory", 127);
		return (EXIT_FAILURE);
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
