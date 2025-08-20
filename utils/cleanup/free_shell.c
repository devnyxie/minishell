/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:44:19 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/20 16:26:03 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->path && shell->path != getenv("PATH"))
		free(shell->path);
	free_2d(shell->envp);
	free_2d(shell->history);
	free_builtins(shell->builtins);
	if (shell->parsed_input)
	{
		free_shell_input(shell->parsed_input);
	}
	free(shell);
}
