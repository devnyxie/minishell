/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:44:19 by tafanasi          #+#    #+#             */
/*   Updated: 2025/07/17 02:49:06 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	// detailed stdout of current shell
	free(shell->prompt);
	free(shell->path);
	free_2d(shell->envp);
	free_2d(shell->history);
	free_builtins(shell->builtins);
	free_shell_input(shell->parsed_input);
	free(shell);
}
