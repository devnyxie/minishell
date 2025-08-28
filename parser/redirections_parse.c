/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:40:54 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/28 17:00:00 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"
#include <stddef.h>

t_redirect_type	redirect_type(t_shell_input *shell_input, t_cmd *cmd)
{
	char			*p;
	t_redirect_type	type;
	int				consumed;

	(void)cmd;
	p = shell_input->input;
	if (!p || *p == '\0')
		return (REDIR_NONE);
	type = get_redirect_type_with_fd(p, &consumed);
	if (type != REDIR_NONE)
		shell_input->input += consumed;
	return (type);
}

static void	handle_redirect_vars(t_shell_input *shell_input,
	t_redirect_data *data)
{
	data->cmd = shell_input->last_cmd;
	data->start_pos = shell_input->input;
	data->fd = parse_fd_number(&shell_input->input);
	data->type = redirect_type(shell_input, data->cmd);
	if (data->type == REDIR_NONE)
	{
		shell_input->input = data->start_pos;
		return ;
	}
	skip_space(&shell_input->input);
	data->expand = 0;
	data->name = grab_filename_or_delim(&shell_input->input,
			(data->type == HEREDOC), &data->expand);
}

void	handle_redirect(t_shell_input *shell_input)
{
	t_redirect_data	data;

	handle_redirect_vars(shell_input, &data);
	if (data.type == REDIR_NONE)
		return ;
	if (!validate_redirect_name(data.name, shell_input))
	{
		free(data.name);
		return ;
	}
	if (!data.cmd)
	{
		handle_redirect_no_cmd(shell_input, &data);
		return ;
	}
	handle_redirect_with_cmd(&data, shell_input);
}
