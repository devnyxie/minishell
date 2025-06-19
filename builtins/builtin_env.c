/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:30:13 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/06/10 10:32:44 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->env_count)
	{
		printf("%s\n", shell->envp[i]);
		i++;
	}
	return (0);
}