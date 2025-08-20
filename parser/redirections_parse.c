/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:40:54 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/20 16:40:55 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"
#include <stddef.h>

static char	*read_quoted_str(char **p)
{
	char	q;
	char	*start;
	size_t	len;
	char	*out;
	size_t	i;

	if (!p || !*p)
		return (NULL);
	q = **p;
	if (q != '\'' && q != '"')
		return (NULL);
	(*p)++;
	start = *p;
	len = 0;
	while (**p && **p != q)
	{
		(*p)++;
		len++;
	}
	if (**p != q)
		return (NULL);
	out = (char *)malloc(len + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (i < len)
		out[i++] = *start++;
	out[len] = '\0';
	(*p)++;
	return (out);
}

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
	t_redirect		*redir;
	int				expand;

	char *name;
	cmd = shell_input->last_cmd;
	type = redirect_type(shell_input, cmd);
	if (type == REDIR_NONE)
		return ;
	skip_space(&shell_input->input);
	expand = 0;
	name = grab_filename_or_delim(&shell_input->input, (type == HEREDOC),
			&expand);
	if (!name || name[0] == '\0')
	{
		report_error(NULL, "syntax error near unexpected token `newline'", 0);
		shell_input->is_valid = 0;
		return ;
	}
	redir = new_redirect_node(type, name);
	if (!redir)
	{
		return ((void)(shell_input->is_valid = 0));
	}
	if (type == HEREDOC)
		redir->expand = expand;
	add_redirect_to_cmd(cmd, redir);
}
