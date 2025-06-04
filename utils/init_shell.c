/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:33:46 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/03 18:00:15 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

t_shell *init_shell(char **envp)
{
    t_shell *shell;
    shell = malloc(sizeof(t_shell));
    if (!shell)
	{
		custom_error("Memory allocation failed\n");
		return (NULL);
	}
    shell->builtins = init_builtins();
    if (!shell->builtins)
    {
        custom_error("Failed to initialize builtins");
        exit(EXIT_FAILURE);
    }
    shell->envp = envp;
    shell->path = getenv("PATH");
    if (!shell->path)
        custom_error("Error! PATH not set\n");
    shell->envp = envp;
    shell->path = getenv("PATH");
    if (!shell->path)
        custom_error("Error! PATH not set\n");
    shell->parsed_input = NULL;
    return (shell);
}