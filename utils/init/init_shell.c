/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:33:46 by tafanasi          #+#    #+#             */
/*   Updated: 2025/07/22 15:36:15 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**copy_envp(t_shell *shell, char **envp)
{
	int	i;

	shell->envp = malloc(sizeof(char *) * (shell->env_capacity + 1));
	if (!shell->envp)
		return (NULL);
	i = 0;
	while (i < shell->env_count)
	{
		shell->envp[i] = ft_strdup(envp[i]);
		if (!shell->envp[i])
		{
			while (--i >= 0)
				free(shell->envp[i]);
			free(shell->envp);
			return (NULL);
		}
		i++;
	}
	shell->envp[shell->env_count] = NULL;
	return (shell->envp);
}

static	int shell_process_check(t_shell *shell)
{
	if (!shell->builtins->builtins_child || !shell->builtins->builtins_parent)
	{
		custom_error("Failed to initialize builtins");
		free(shell);
		return (1);
	}
	return (0);
}

static int copy_env_check(t_shell *shell, char **envp)
{
	if (!copy_envp(shell, envp))
	{
		custom_error("Failed to copy environment");
		free(shell->builtins);
		free(shell);
		return (1);
	}
	return (0);
}

t_shell	*init_shell(char **envp)
{
	t_shell *shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
	{
		custom_error("Memory allocation failed\n");
		return (NULL);
	}
	shell->env_count = env_count(envp);
	shell->env_capacity = env_count(envp) + 10; // extra space for new vars
	shell->builtins = malloc(sizeof(t_builtins_unified));
	shell->builtins->builtins_child = init_builtins_child();
	shell->builtins->builtins_parent = init_builtins_parent();
	if (shell_process_check(shell))
		exit(EXIT_FAILURE);
	if (copy_env_check(shell, envp))
		return (NULL);
	shell->path = getenv("PATH");
	if (!shell->path)
		custom_error("Error! PATH not set\n");
	shell->parsed_input = NULL;
	shell->history = NULL;
	shell->prompt = NULL;
	shell->exit_code = 0;
	return (shell);
}
