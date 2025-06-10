/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:27:22 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/06/10 17:38:40 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_export(t_shell *shell, char **args)
{
	int	i;
	char	*equals;
	
	i = 0;
	if (args[1] == NULL)
	{
		while (i < shell->env_count)
		{
			printf("declare -x %s\n", shell->envp[i]);
			i++;
		}
		return (0);
	}
	equals = ft_strchr(args[1], '=');
	if (equals)
	{
		*equals = '\0';
		update_env_var(shell, args[1], equals + 1);
		*equals = '=';
	}
	else
		update_env_var(shell, args[1], "");
	
	return (0);
}
