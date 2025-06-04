/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/06/04 16:11:57 by tafanasi         ###   ########.fr       */
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