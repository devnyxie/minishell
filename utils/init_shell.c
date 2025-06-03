/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:33:46 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/03 17:45:33 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_shell *init_shell(void)
{
    t_shell *shell;
    shell = malloc(sizeof(t_shell));
    if (!shell)
	{
		custom_error("Memory allocation failed\n");
		return (1);
	}
    shell->builtins = init_builtins();
    if (!shell->builtins)
    {
        custom_error("Failed to initialize builtins");
        exit(EXIT_FAILURE);
    }
    shell->envp = NULL;
    shell->parsed_input = NULL;
    return (shell);
}