/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 02:28:29 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/22 13:36:52 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_shell_input	*init_shell_input(char *input)
{
	t_shell_input	*shell_input;

	shell_input = malloc(sizeof(t_shell_input));
	if (!shell_input)
		return (NULL);
	shell_input->first_cmd = NULL;
	shell_input->last_cmd = NULL;
	shell_input->is_valid = 1;
	shell_input->incomplete_pipe = 0;
	shell_input->cmds_count = 0;
	shell_input->input = input;
	return (shell_input);
}
