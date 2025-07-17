/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 01:52:53 by tafanasi          #+#    #+#             */
/*   Updated: 2025/07/17 02:52:09 by tafanasi         ###   ########.fr       */
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
			for (i = 0; tmp->args[i]; i++)
				free(tmp->args[i]);
			free(tmp->args);
		}
		free_redirects(tmp->in_redir);
		free_redirects(tmp->out_redir);
		free(tmp);
	}
}
