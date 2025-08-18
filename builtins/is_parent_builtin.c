/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_parent_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:11:56 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/08 11:23:25 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../structs.h"

int	is_parent_builtin(t_shell *shell, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!shell || !shell->builtins || !cmd->name)
	{
		printf("not valid inputs");
		return (0);
	}
	while (shell->builtins->builtins_parent[i].name)
	{
		if (ft_strcmp(shell->builtins->builtins_parent[i].name, cmd->name) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}
