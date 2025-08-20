/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:11:38 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/20 15:45:08 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	normalize_exit_code(int n)
{
	int	code;

	code = n % 256;
	if (code < 0)
		code = 256 + code;
	return (code);
}

static int	process_exit_args(char **args, int arg_count, int *out_code)
{
	if (arg_count <= 1)
	{
		*out_code = 0;
		return (0);
	}
	if (!is_valid_number(args[1]))
	{
		report_error("minishell: exit", "numeric argument required", 0);
		*out_code = 2;
		return (0);
	}
	if (arg_count > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	*out_code = normalize_exit_code(ft_atoi(args[1]));
	return (0);
}

int	exit_shell(t_shell *shell, char **args)
{
	int	arg_count;
	int	exit_code;
	int	status;

	printf("exit\n");
	arg_count = count_args(args);
	status = process_exit_args(args, arg_count, &exit_code);
	if (status == 1)
	{
		shell->exit_code = 1;
		return (1);
	}
	shell->exit_code = exit_code;
	exit(exit_code);
	return (exit_code);
}
