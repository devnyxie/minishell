/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parse_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:45:00 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/27 15:45:00 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

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
	if (!(*p)[i] || ((*p)[i] != '>' && (*p)[i] != '<'))
		return (-1);
	*p += i;
	return (fd);
}

static t_redirect_type	get_redirect_type_and_advance(char *p,
		t_shell_input *shell_input)
{
	if (*p == '>' && *(p + 1) == '>')
	{
		shell_input->input += 2;
		return (REDIR_APPEND);
	}
	else if (*p == '<' && *(p + 1) == '<')
	{
		shell_input->input += 2;
		return (HEREDOC);
	}
	else if (*p == '>')
	{
		shell_input->input += 1;
		return (REDIR_OUT);
	}
	else if (*p == '<')
	{
		shell_input->input += 1;
		return (REDIR_IN);
	}
	return (REDIR_NONE);
}

int	parse_redirect_fd_and_type(t_shell_input *shell_input,
		t_redirect_type *type, int *fd)
{
	char	*start_pos;

	start_pos = shell_input->input;
	*fd = parse_fd_number(&shell_input->input);
	*type = get_redirect_type_and_advance(shell_input->input, shell_input);
	if (*type == REDIR_NONE)
	{
		shell_input->input = start_pos;
		return (0);
	}
	return (1);
}

t_redirect_type	redirect_type(t_shell_input *shell_input, t_cmd *cmd)
{
	char	*input;

	(void)cmd;
	input = shell_input->input;
	if (*input == '>' && *(input + 1) == '>')
	{
		shell_input->input += 2;
		return (REDIR_APPEND);
	}
	if (*input == '<' && *(input + 1) == '<')
	{
		shell_input->input += 2;
		return (HEREDOC);
	}
	if (*input == '>')
	{
		shell_input->input += 1;
		return (REDIR_OUT);
	}
	if (*input == '<')
	{
		shell_input->input += 1;
		return (REDIR_IN);
	}
	return (REDIR_NONE);
}
