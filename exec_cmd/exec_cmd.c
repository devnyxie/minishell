/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:04:38 by tafanasi          #+#    #+#             */
/*   Updated: 2025/07/17 11:58:22 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"

void	exec_cmd(t_cmd *cmd, t_shell *shell, char **args)
{
	start_process(cmd, -1, shell, args);
}