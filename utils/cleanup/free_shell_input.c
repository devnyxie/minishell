/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 01:53:16 by tafanasi          #+#    #+#             */
/*   Updated: 2025/07/17 11:44:39 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_shell_input(t_shell_input *shell_input)
{
	if (!shell_input)
		return ;
	free_cmds(shell_input->first_cmd);
	// Don't free shell_input->input here as it's already freed in handle_expand_variables
	// free(shell_input->input); // allocated using readline
	free(shell_input);
}