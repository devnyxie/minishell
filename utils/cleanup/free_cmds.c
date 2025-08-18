/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 01:52:53 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/08 11:59:03 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free(tmp->name);
		if (tmp->args)
		{
			i = 0;
			while (tmp->args[i])
			{
				free(tmp->args[i]);
				i++;
			}
			// for (i = 0; tmp->args[i]; i++)
			// 	free(tmp->args[i]);
			free(tmp->args);
		}
		free_redirects(tmp->in_redir);
		free_redirects(tmp->out_redir);
		free(tmp);
	}
}
