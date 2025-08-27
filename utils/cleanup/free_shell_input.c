/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 01:53:16 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/27 12:46:25 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_shell_input(t_shell_input *shell_input)
{
	if (!shell_input)
		return ;
	free_cmds(shell_input->first_cmd);
	free_redirects(shell_input->pending_in_redir);
	free_redirects(shell_input->pending_out_redir);
	free(shell_input);
}
