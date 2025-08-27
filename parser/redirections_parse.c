/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parse_new.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:40:54 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/27 15:45:00 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"
#include <stddef.h>

static char	*grab_filename_or_delim(char **p, int is_hd, int *expand)
{
	char	*tok;

	if (!p || !*p)
		return (NULL);
	if (is_hd && (**p == '\'' || **p == '"'))
	{
		tok = read_quoted_str(p);
		if (!tok)
			return (NULL);
		if (expand)
			*expand = 0;
		return (tok);
	}
	tok = grab_word(p);
	if (!tok)
		return (NULL);
	if (expand)
	{
		if (is_hd)
			*expand = 1;
		else
			*expand = 0;
	}
	return (tok);
}

static int	get_redirect_name(t_shell_input *shell_input, t_redirect_type type,
		char **name, int *expand)
{
	*expand = 0;
	*name = grab_filename_or_delim(&shell_input->input, (type == HEREDOC),
			expand);
	if (!validate_redirect_name(*name, shell_input))
	{
		free(*name);
		return (0);
	}
	return (1);
}

static void	handle_redirect_with_cmd(t_shell_input *shell_input,
		t_redirect_params *params)
{
	t_redirect_info	info;
	t_cmd			*cmd;

	cmd = shell_input->last_cmd;
	info = (t_redirect_info){params->name, params->type, params->expand,
		cmd, shell_input};
	create_and_add_redirect(&info);
	set_redirect_fd_on_cmd(cmd, params->fd, params->type);
}

void	handle_redirect(t_shell_input *shell_input)
{
	t_redirect_type		type;
	int					expand;
	char				*name;
	int					fd;
	t_redirect_params	params;

	if (!parse_redirect_fd_and_type(shell_input, &type, &fd))
		return ;
	skip_space(&shell_input->input);
	if (!get_redirect_name(shell_input, type, &name, &expand))
		return ;
	params = (t_redirect_params){type, name, fd, expand};
	if (!shell_input->last_cmd)
	{
		store_pending_redirect(shell_input, &params);
		return ;
	}
	handle_redirect_with_cmd(shell_input, &params);
}

void	parse_one_redirection(t_cmd *cmd, t_shell_input *in)
{
	t_redirect_type	type;
	char			*name;
	t_redirect_info	info;

	type = redirect_type(in, cmd);
	if (type == REDIR_NONE)
		return ;
	skip_space(&in->input);
	name = grab_word(&in->input);
	if (!validate_redirect_name(name, in))
	{
		free(name);
		return ;
	}
	info = (t_redirect_info){name, type, 1, cmd, in};
	create_and_add_redirect(&info);
}
