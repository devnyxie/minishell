/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:04:38 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/05 14:51:35 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "../minishell.h"

void	exec_cmd(t_cmd *cmd, t_shell *shell, char **args)
{
	if (prepare_heredocs(cmd, shell) < 0)
	{
		shell->exit_code = 1;
		return ;
	}
	prune_heredocs(cmd);
	start_process(cmd, -1, shell, args);
}

