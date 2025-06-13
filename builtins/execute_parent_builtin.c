/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parent_builtin.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:16:09 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/13 17:34:39 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Execute a builtin command
int execute_parent_builtin(t_shell *shell, char **args, t_cmd *cmd)
{
    int i = 0;
    if (!shell || !shell->builtins->builtins_parent || !args || !args[0]){
    	return (-1);
    }
    
    while (shell->builtins->builtins_parent[i].name)
    {
        if (ft_strcmp(shell->builtins->builtins_parent[i].name, cmd->name) == 0)
        {
            if (shell->builtins->builtins_parent[i].fn)
			{
                return (shell->builtins->builtins_parent[i].fn(shell, cmd->args));
            }
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