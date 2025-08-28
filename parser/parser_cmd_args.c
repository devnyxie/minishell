/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:00:00 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/28 17:00:00 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

static void	set_redirect_fd(t_redirect *redir, int fd)
{
	while (redir && redir->next)
		redir = redir->next;
	if (redir)
		redir->fd = fd;
}

static int	init_redirection_data(t_cmd *cmd, t_shell_input *in,
	t_redirect_data *data)
{
	data->start_pos = in->input;
	data->fd = parse_fd_number(&in->input);
	data->type = redirect_type(in, cmd);
	if (data->type == REDIR_NONE)
	{
		in->input = data->start_pos;
		return (0);
	}
	skip_space(&in->input);
	data->expand = 0;
	data->name = grab_filename_or_delim(&(in->input),
			(data->type == HEREDOC), &data->expand);
	return (1);
}

static void	process_redirection(t_cmd *cmd, t_shell_input *in,
	t_redirect_data *data)
{
	t_redirect_info	info;

	if (!validate_redirect_name(data->name, in))
		return ;
	info = (t_redirect_info){data->name, data->type, data->expand, cmd, in};
	create_and_add_redirect(&info);
	if (data->fd != -1)
	{
		if (data->type == REDIR_IN || data->type == HEREDOC)
			set_redirect_fd(cmd->in_redir, data->fd);
		else
			set_redirect_fd(cmd->out_redir, data->fd);
	}
}

void	parse_one_redirection(t_cmd *cmd, t_shell_input *in)
{
	t_redirect_data	data;

	if (!init_redirection_data(cmd, in, &data))
		return ;
	process_redirection(cmd, in, &data);
}
