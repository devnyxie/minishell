/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:27:22 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/06/16 15:16:47 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	sort_env(t_shell *shell)
{
	int	i = 0;
	int j = 0;
	char	*temp;
	
	while (i < shell->env_count - 1)
	{
		j = 0;
		while (j < shell->env_count - 1 - i)
		{
			if (ft_strcmp(shell->envp[j], shell->envp[j+1]) > 0)
			{
				temp = shell->envp[j];
				shell->envp[j] = shell->envp[j+1];
				shell->envp[j+1] = temp;
			}
			j++;
		}
		i++;
	}
	
}

int	builtin_export(t_shell *shell, char **args)
{
	int	i;
	char	*equals;
	
	i = 0;
	if (args[1] == NULL)
	{
		sort_env(shell);
		while (i < shell->env_count)
		{
			printf("declare -x %s\n", shell->envp[i]);
			i++;
		}
		return (0);
	}
	i = 1;
	while(args[i])
	{
		if (is_valid_identifier(args[i]))
		{
			printf("Not valid identifier - \n");
			return (1);
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
		i++;
	}
	return (0);
}
