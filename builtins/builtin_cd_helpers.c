/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:04:15 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/20 16:18:02 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	replace_env_at_index(t_shell *shell, int index, char *new_var)
{
	if (index >= 0 && index < shell->env_count)
	{
		free(shell->envp[index]);
		shell->envp[index] = new_var;
	}
}

static void	append_env_entry(t_shell *shell, char *new_var)
{
	if (!grow_envp_if_needed(shell))
	{
		free(new_var);
		return ;
	}
	shell->envp[shell->env_count] = new_var;
	shell->env_count++;
	shell->envp[shell->env_count] = NULL;
}

static char	*make_env_pair(char *name, const char *value)
{
	size_t	total;
	char	*str;

	if (!name || !value)
		return (NULL);
	total = ft_strlen(name) + ft_strlen(value) + 2;
	str = malloc(total);
	if (!str)
		return (NULL);
	ft_strcpy(str, name);
	ft_strlcat(str, "=", total);
	ft_strlcat(str, value, total);
	return (str);
}

static void	update_path_cache_from_env(t_shell *shell)
{
	const char	*path_value;

	if (!shell)
		return ;
	path_value = get_env_var(shell, "PATH");
	if (shell->path && shell->path != getenv("PATH"))
		free(shell->path);
	if (path_value && *path_value != '\0')
		shell->path = ft_strdup(path_value);
	else
		shell->path = NULL;
}

void	update_env_var(t_shell *shell, char *var_name, const char *value)
{
	int		index;
	char	*new_var;

	if (!shell || !var_name || !value)
		return ;
	new_var = make_env_pair(var_name, value);
	if (!new_var)
		return ;
	index = find_env_var(shell, var_name);
	if (index != -1)
		replace_env_at_index(shell, index, new_var);
	else
		append_env_entry(shell, new_var);
	if (ft_strcmp(var_name, "PATH") == 0)
		update_path_cache_from_env(shell);
}
