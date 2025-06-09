/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:11:56 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/06/09 16:12:20 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Check if a command is a builtin
int is_builtin(t_shell *shell, char *cmd_name)
{
    int i = 0;
    
    if (!shell || !shell->builtins || !cmd_name)
        return (0);
    
    while (shell->builtins[i].name)
    {
        if (ft_strcmp(shell->builtins[i].name, cmd_name) == 0)
            return (1);
        i++;
    }
    return (0);
}