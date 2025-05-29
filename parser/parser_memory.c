/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:02:53 by tafanasi          #+#    #+#             */
/*   Updated: 2025/05/29 18:47:02 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_redirects(t_redirect *redir)
{
	t_redirect	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		free(tmp->file);
		free(tmp);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	if (cmd)
	{
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
			// if (tmp->in_redir)
			// 	free_redirects(tmp->in_redir);
			// if (tmp->out_redir)
			// 	free_redirects(tmp->out_redir);
			free(tmp);
		}
	}
}

void	free_shell_input(t_shell_input *input)
{
	if (!input)
		return ;
	// free_cmd(input->first_cmd);
	// free_cmd(input->last_cmd);
	free(input);
	// free(input);
}
