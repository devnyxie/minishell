/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:12:20 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/20 16:18:07 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	grow_envp_if_needed(t_shell *shell)
{
	char	**new_envp;
	int		new_cap;

	if (shell->env_count < shell->env_capacity)
		return (1);
	new_cap = shell->env_capacity * 2;
	new_envp = realloc(shell->envp, sizeof(char *) * (new_cap + 1));
	if (!new_envp)
		return (0);
	shell->envp = new_envp;
	shell->env_capacity = new_cap;
	shell->envp[shell->env_count] = NULL;
	return (1);
}

int	find_env_var(t_shell *shell, const char *var_name)
{
	int	len;
	int	i;

	if (!shell || !var_name || !shell->envp)
		return (-1);
	i = 0;
	len = ft_strlen(var_name);
	while (i < shell->env_count)
	{
		if (shell->envp[i] && ft_strncmp(shell->envp[i], var_name, len) == 0
			&& shell->envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_env_var(t_shell *shell, const char *var_name)
{
	int		index;
	char	*equals;

	if (!shell || !var_name)
		return (NULL);
	index = find_env_var(shell, var_name);
	if (index != -1)
	{
		equals = ft_strchr(shell->envp[index], '=');
		if (equals)
			return (equals + 1);
	}
	return (NULL);
}
