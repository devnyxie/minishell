/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:00:00 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/28 17:00:00 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

int	is_end_simple(char c)
{
	if (c == '|' || c == '\0')
		return (1);
	return (0);
}

int	at_redir(const char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	if (*s == '>' || *s == '<')
		return (1);
	i = 0;
	if (ft_isdigit(s[i]))
	{
		while (s[i] && ft_isdigit(s[i]))
			i++;
		if (s[i] == '>' || s[i] == '<')
			return (1);
	}
	return (0);
}

static int	init_cmd_args(t_cmd *cmd, char *cmd_name)
{
	cmd->args = malloc(sizeof(char *) * 256);
	if (!cmd->args)
		return (0);
	cmd->args[0] = ft_strdup(cmd_name);
	if (!cmd->args[0])
	{
		free(cmd->args);
		return (0);
	}
	return (1);
}

static int	process_arg_loop(t_cmd *cmd, t_cmd_params *params, int *arg_count)
{
	char	*arg;

	while (*(params->shell_input->input)
		&& !is_end_simple(*(params->shell_input->input)))
	{
		skip_space(&(params->shell_input->input));
		if (!*(params->shell_input->input)
			|| is_end_simple(*(params->shell_input->input)))
			break ;
		if (at_redir(params->shell_input->input))
		{
			parse_one_redirection(cmd, params->shell_input);
			if (!params->shell_input->is_valid)
				break ;
			continue ;
		}
		arg = grab_word_with_env(&(params->shell_input->input),
				params->envp, params->shell);
		if (!arg)
			break ;
		cmd->args[(*arg_count)++] = arg;
	}
	return (1);
}

void	handle_args(t_cmd *cmd, char *cmd_name, t_cmd_params *params)
{
	int	arg_count;

	if (!init_cmd_args(cmd, cmd_name))
		return ;
	arg_count = 1;
	process_arg_loop(cmd, params, &arg_count);
	cmd->args[arg_count] = NULL;
}
