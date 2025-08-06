/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_parent_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:11:56 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/06 14:18:41 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../structs.h"

int	is_parent_builtin(t_shell *shell, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!shell || !shell->builtins || !cmd->name){
		printf("not valid inputs");
		return (0);
	}
	while (shell->builtins->builtins_parent[i].name)
	{
		printf("Comparing shell's %s with requested %s\n", shell->builtins->builtins_parent[i].name, cmd->name);
		if (ft_strcmp(shell->builtins->builtins_parent[i].name, cmd->name) == 0){
			printf("is builtin\n");
			return (1);
		}
		i++;
	}
	return (0);
}
