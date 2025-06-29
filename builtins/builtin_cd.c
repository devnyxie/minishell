/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:02:54 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/06/29 13:04:58 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (shell->envp[i] && ft_strncmp(shell->envp[i], var_name, len) == 0 &&
			shell->envp[i][len] == '=')
		{
			return (i); // ret the position in env list
			printf("%s\n", shell->envp[i]);
		}
		i++;
	}
	return (-1);
}

void	update_env_var(t_shell *shell, char *var_name, const char *value)
{
	char	*new_var;
	int		index;
	int		total_len;
	
	if (!shell || !var_name || !value)
		return;
	// Calculate total length: var_name + '=' + value + '\0'
	total_len = ft_strlen(var_name) + ft_strlen(value) + 2;
	// Create the new environment variable string "VAR=value"
	new_var = malloc(total_len);
	if (!new_var)
		return;
	// Format the string properly
	ft_strcpy(new_var, var_name);
	ft_strlcat(new_var, "=", total_len);
	ft_strlcat(new_var, value, total_len);
	index = find_env_var(shell, var_name);
	if (index != -1)
	{
		// Variable exists, update it
		free(shell->envp[index]);
		shell->envp[index] = new_var;
	}
	else
	{
		// Variable doesn't exist, add it
		if (shell->env_count >= shell->env_capacity)
		{
			shell->env_capacity *= 2;
			char **new_envp = realloc(shell->envp, sizeof(char*) * (shell->env_capacity + 1));
			if (!new_envp)
			{
				free(new_var);
				return;
			}
			shell->envp = new_envp;
		}
		shell->envp[shell->env_count] = new_var;
		shell->env_count++;
		shell->envp[shell->env_count] = NULL;
	}
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

int	builtin_cd(t_shell *shell, char **args)
{
	int		i;
	char	*path;
	char	*old_pwd;
	char	cwd[PATH_MAX];

	if (!shell || !args)
		return (1);
	old_pwd = get_env_var(shell, "PWD");
	i = 0;
	while (args[i])
		i++;
	if (args[1] == NULL)
	{
		path = get_env_var(shell, "HOME");
		if (!path)
			exit(EXIT_FAILURE);
	}
	else
		path = args[1];
	if (chdir(path) == -1)
		report_error("cd", path, 1);
	if (old_pwd)
		update_env_var(shell, "OLDPWD", old_pwd);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		update_env_var(shell, "PWD", cwd);
	else
		report_error("getcwd", cwd, 1);
	return (0);
}
