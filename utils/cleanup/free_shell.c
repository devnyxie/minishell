/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:44:19 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/20 12:07:49 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	// free(shell->prompt);
	// Free shell->path if it was dynamically allocated (not pointing to system getenv)
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
