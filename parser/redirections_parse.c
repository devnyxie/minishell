/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:40:54 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/27 12:46:25 by tafanasi         ###   ########.fr       */
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

static int	parse_fd_number(char **p)
{
	int	fd;
	int	i;

	if (!*p || !**p || !ft_isdigit(**p))
		return (-1);
	
	fd = 0;
	i = 0;
	while ((*p)[i] && ft_isdigit((*p)[i]))
	{
		fd = fd * 10 + ((*p)[i] - '0');
		i++;
	}
	
	// Check if we have a valid redirection operator after the number
	if (!(*p)[i] || ((*p)[i] != '>' && (*p)[i] != '<'))
		return (-1);
	
	*p += i;  // Move pointer past the fd number
	return (fd);
}

static t_redirect_type	get_redirect_type_with_fd(char *p, int *consumed)
{
	t_redirect_type	type;

	*consumed = 0;
	if (*p == '>' && *(p + 1) == '>')
	{
		type = REDIR_APPEND;
		*consumed = 2;
	}
	else if (*p == '<' && *(p + 1) == '<')
	{
		type = HEREDOC;
		*consumed = 2;
	}
	else if (*p == '>')
	{
		type = REDIR_OUT;
		*consumed = 1;
	}
	else if (*p == '<')
	{
		type = REDIR_IN;
		*consumed = 1;
	}
	else
		return (REDIR_NONE);
	return (type);
}

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

void	handle_redirect(t_shell_input *shell_input)
{
	t_cmd			*cmd;
	t_redirect_type	type;
	int				expand;
	char			*name;
	t_redirect_info	info;
	int				fd;
	char			*start_pos;

	cmd = shell_input->last_cmd;
	start_pos = shell_input->input;
	
	// Try to parse file descriptor number
	fd = parse_fd_number(&shell_input->input);
	
	type = redirect_type(shell_input, cmd);
	if (type == REDIR_NONE)
	{
		// Reset if we couldn't parse a valid redirection
		shell_input->input = start_pos;
		return ;
	}
	
	skip_space(&shell_input->input);
	expand = 0;
	name = grab_filename_or_delim(&shell_input->input, (type == HEREDOC),
			&expand);
	if (!validate_redirect_name(name, shell_input))
	{
		free(name);
		return ;
	}
	
	// If no command exists yet, store the redirection as pending
	if (!cmd)
	{
		t_redirect *redir;
		
		if (fd != -1)
			redir = new_redirect_node_with_fd(type, name, fd);
		else
			redir = new_redirect_node(type, name);
			
		if (!redir)
		{
			shell_input->is_valid = 0;
			return ;
		}
		if (type == HEREDOC)
			redir->expand = expand;
		
		// Add to appropriate pending list
		if (type == REDIR_IN || type == HEREDOC)
		{
			t_redirect **head = &shell_input->pending_in_redir;
			if (!*head)
				*head = redir;
			else
			{
				t_redirect *cur = *head;
				while (cur->next)
					cur = cur->next;
				cur->next = redir;
			}
		}
		else
		{
			t_redirect **head = &shell_input->pending_out_redir;
			if (!*head)
				*head = redir;
			else
			{
				t_redirect *cur = *head;
				while (cur->next)
					cur = cur->next;
				cur->next = redir;
			}
		}
		return ;
	}
	
	// If command exists, add redirection to it normally
	info = (t_redirect_info){name, type, expand, cmd, shell_input};
	create_and_add_redirect(&info);
	
	// Set fd if it was specified
	if (fd != -1 && cmd->out_redir)
	{
		t_redirect *redir = cmd->out_redir;
		while (redir->next)
			redir = redir->next;
		redir->fd = fd;
	}
	else if (fd != -1 && cmd->in_redir)
	{
		t_redirect *redir = cmd->in_redir;
		while (redir->next)
			redir = redir->next;
		redir->fd = fd;
	}
}

void	parse_one_redirection(t_cmd *cmd, t_shell_input *in)
{
	t_redirect_type	type;
	char			*name;
	int				expand;
	t_redirect_info	info;
	int				fd;
	char			*start_pos;

	start_pos = in->input;
	
	// Try to parse file descriptor number
	fd = parse_fd_number(&in->input);
	
	type = redirect_type(in, cmd);
	if (type == REDIR_NONE)
	{
		// Reset if we couldn't parse a valid redirection
		in->input = start_pos;
		return ;
	}
	
	skip_space(&in->input);
	expand = 0;
	name = grab_filename_or_delim(&(in->input), (type == HEREDOC), &expand);
	if (!validate_redirect_name(name, in))
	{
		return ;
	}
	
	info = (t_redirect_info){name, type, expand, cmd, in};
	create_and_add_redirect(&info);
	
	// Set fd if it was specified
	if (fd != -1)
	{
		t_redirect *redir;
		if (type == REDIR_IN || type == HEREDOC)
			redir = cmd->in_redir;
		else
			redir = cmd->out_redir;
			
		// Find the last redirection (the one we just added)
		while (redir && redir->next)
			redir = redir->next;
		if (redir)
			redir->fd = fd;
	}
}
