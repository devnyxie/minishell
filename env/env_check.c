/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:25:22 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/06/19 11:22:35 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// here we're checking if we have a valid name for env var
int	is_valid_identifier(char *name)
{
	int	i;

	i = 0;
	if (!name || !*name)
		return (0);
	if (ft_isalnum(name[0]) == 0 && name[0] != '_')
		return (0);
	i++;
	while (name[i] && name[i] != '=')
	{
		if (ft_isalpha(name[i]) == 0 && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	unset_env_var(char *name, t_shell *shell)
{
	int	i;
	int	j;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (shell->envp[i])
	{
		// try to find var to remove
		if (ft_strncmp(shell->envp[i], name, name_len) == 0 &&
			shell->envp[i][name_len] == '=')
		{
			free(shell->envp[i]);
			j = i;
			while (shell->envp[j])
			{
				shell->envp[j] = shell->envp[j + 1];
				j++;
			}
			// resize array TODO
		}
		i++;
	}
}