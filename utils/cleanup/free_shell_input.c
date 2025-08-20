/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 01:53:16 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/20 16:25:57 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_shell_input(t_shell_input *shell_input)
{
	if (!shell_input)
		return ;
	free_cmds(shell_input->first_cmd);
	free(shell_input);
}
