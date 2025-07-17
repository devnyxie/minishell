/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:44:19 by tafanasi          #+#    #+#             */
/*   Updated: 2025/07/17 12:29:53 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	free(shell->prompt);
	// Don't free shell->path as it points to getenv("PATH") which is managed by the system
	// free(shell->path);
	free_2d(shell->envp);
	free_2d(shell->history);
	free_builtins(shell->builtins);
	if (shell->parsed_input)
		free_shell_input(shell->parsed_input);
	free(shell);
}
