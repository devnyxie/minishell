/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:53:17 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/06/09 15:53:43 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Execute a builtin command
int execute_builtin(t_shell *shell, char **args)
{
    int i = 0;
    
    if (!shell || !shell->builtins || !args || !args[0])
        return (-1);
    
    while (shell->builtins[i].name)
    {
        if (ft_strcmp(shell->builtins[i].name, args[0]) == 0)
        {
            if (shell->builtins[i].fn)
                return (shell->builtins[i].fn(shell, args));
            else
            {
                printf("%s: builtin not implemented yet\n", args[0]);
                return (1);
            }
        }
        i++;
    }
    return (-1); // Not found
}