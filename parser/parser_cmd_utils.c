/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:30:00 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/27 15:30:00 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_variable_assignment(char *cmd_name)
{
	int	i;

	if (!cmd_name || !*cmd_name)
		return (0);
	if (!ft_isalpha(cmd_name[0]) && cmd_name[0] != '_')
		return (0);
	i = 1;
	while (cmd_name[i] && cmd_name[i] != '=')
	{
		if (!ft_isalnum(cmd_name[i]) && cmd_name[i] != '_')
			return (0);
		i++;
	}
	return (cmd_name[i] == '=');
}

static void	handle_variable_assignment(char *assignment, t_shell *shell)
{
	char	*equals;
	char	*var_name;
	char	*var_value;

	equals = ft_strchr(assignment, '=');
	if (!equals)
		return ;
	*equals = '\0';
	var_name = assignment;
	var_value = equals + 1;
	if (is_valid_identifier(var_name))
		update_env_var(shell, var_name, var_value);
	*equals = '=';
}

int	check_and_handle_variable_assignment(char *cmd_name, t_shell *shell)
{
	if (is_variable_assignment(cmd_name))
	{
		handle_variable_assignment(cmd_name, shell);
		return (1);
	}
	return (0);
}
