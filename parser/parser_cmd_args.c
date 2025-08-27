/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:30:00 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/27 15:30:00 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_end_simple(char c)
{
	if (c == '|' || c == '\0')
		return (1);
	return (0);
}

static int	at_redir(const char *s)
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

void	handle_args(t_cmd *cmd, char *cmd_name, t_cmd_params *params)
{
	int		arg_count;
	char	*arg;

	arg_count = 0;
	cmd->args = malloc(sizeof(char *) * 256);
	if (!cmd->args)
		return ;
	cmd->args[arg_count++] = ft_strdup(cmd_name);
	while (!is_end_simple(*(params->shell_input->input)))
	{
		skip_space(&(params->shell_input->input));
		if (is_end_simple(*(params->shell_input->input)))
			break ;
		if (at_redir(params->shell_input->input))
		{
			redirections_parse(params->shell_input);
			continue ;
		}
		arg = grab_word_with_env(&(params->shell_input->input),
				params->envp, params->shell);
		if (arg)
			cmd->args[arg_count++] = arg;
	}
	cmd->args[arg_count] = NULL;
	cmd->args_count = arg_count;
}
