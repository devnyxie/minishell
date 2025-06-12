/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:02:54 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/06/12 16:02:27 by mmitkovi         ###   ########.fr       */
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
	printf("---Inside get_env_var---\n");
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
	char	*path;
	char	*old_pwd;
	char	cwd[PATH_MAX];

	if (!shell || !args)
		return (1);
	printf("---Inside builtin_cd---\n");
	old_pwd = get_env_var(shell, "PWD");
	printf("Old PWD: %s\n", old_pwd);
	//determine target dir
	int i = 0;
	while (args[i])
	{
		printf("Args inside builtin_cd: %s\n", args[i]);
		i++;
	}
	if (args[1] == NULL)
	{
		//no args, go HOME
		printf("No args after cd command\n");
		path = get_env_var(shell, "HOME");
		printf("Path: %s\n", path);
		if (!path)
			exit(EXIT_FAILURE);
	}
	else
		path = args[1];
	// change dir
	printf("Path for chdir: %s\n", path);
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	// update OLDPWD with previous PWD
	if (old_pwd)
		update_env_var(shell, "OLDPWD", old_pwd);

	// update PWD with current dir
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		update_env_var(shell, "PWD", cwd);
	else
	{
		perror("getcwd");
		return (1);
	}
	return (0);
}