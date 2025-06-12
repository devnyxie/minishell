/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:11:56 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/06/12 12:12:37 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../structs.h"

// Check if a command is a builtin
int is_builtin(t_shell *shell, t_cmd *cmd)
{
    int i = 0;
    
    if (!shell || !shell->builtins || !cmd->name)
        return (0);
    printf("Cmd name: %s\n", cmd->name);
    while (shell->builtins[i].name)
    {
        if (ft_strcmp(shell->builtins[i].name, cmd->name) == 0)
            return (1);
        i++;
    }
    return (0);
}