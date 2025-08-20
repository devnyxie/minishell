/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:11:38 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/20 11:53:42 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_shell(t_shell *shell, char **args)
{
	int	exit_code;
	int	arg_count;

	printf("exit\n");
	arg_count = count_args(args);
	exit_code = 0;
	if (arg_count > 1)
	{
		if (!is_valid_number(args[1]))
		{
			report_error("minishell: exit", "numeric argument required", 0);
			exit_code = 2;
		}
		else if (arg_count > 2)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
			shell->exit_code = 1;
			return (1);
		}
		else
		{
			exit_code = ft_atoi(args[1]) % 256;
			if (exit_code < 0)
				exit_code = 256 + exit_code;
		}
	}
	shell->exit_code = exit_code;
	exit(exit_code);
	return (exit_code);
}
