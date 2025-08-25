/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:40:54 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/22 16:59:29 by mmitkovi         ###   ########.fr       */
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

t_redirect_type	redirect_type(t_shell_input *shell_input, t_cmd *cmd)
{
	char			*p;
	t_redirect_type	type;

	(void)cmd;
	p = shell_input->input;
	if (!p || *p == '\0')
		return (REDIR_NONE);
	if (*p == '>' && *(p + 1) == '>')
		type = REDIR_APPEND;
	else if (*p == '<' && *(p + 1) == '<')
		type = HEREDOC;
	else if (*p == '>')
		type = REDIR_OUT;
	else if (*p == '<')
		type = REDIR_IN;
	else
		return (REDIR_NONE);
	if (type == REDIR_APPEND || type == HEREDOC)
		shell_input->input += 2;
	else
		shell_input->input += 1;
	return (type);
}

void	handle_redirect(t_shell_input *shell_input)
{
	t_cmd			*cmd;
	t_redirect_type	type;
	int				expand;
	char			*name;
	t_redirect_info	info;

	cmd = shell_input->last_cmd;
	type = redirect_type(shell_input, cmd);
	if (type == REDIR_NONE)
		return ;
	if (!cmd)
		cmd = create_empty_cmd(shell_input);
	if (!cmd)
		return ;
	skip_space(&shell_input->input);
	expand = 0;
	name = grab_filename_or_delim(&shell_input->input, (type == HEREDOC),
			&expand);
	if (!validate_redirect_name(name, shell_input))
	{
		free (name);
		return ;
	}
	info = (t_redirect_info){name, type, expand, cmd, shell_input};
	create_and_add_redirect(&info);
}

void	parse_one_redirection(t_cmd *cmd, t_shell_input *in)
{
	t_redirect_type	type;
	char			*name;
	int				expand;
	t_redirect_info	info;

	type = redirect_type(in, cmd);
	if (type == REDIR_NONE)
		return ;
	skip_space(&in->input);
	expand = 0;
	name = grab_filename_or_delim(&(in->input), (type == HEREDOC), &expand);
	if (!validate_redirect_name(name, in))
		return ;
	info = (t_redirect_info){name, type, expand, cmd, in};
	create_and_add_redirect(&info);
}

