/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:12:12 by tafanasi          #+#    #+#             */
/*   Updated: 2025/07/17 02:30:32 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// to-be-reviewed
void	custom_error(char *msg)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	while (*msg)
	{
		if (*msg == '\n')
			write(STDERR_FILENO, "\n", 1);
		else
			write(STDERR_FILENO, msg, 1);
		msg++;
	}
}

void	report_error(char *command, char *detail, int is_sys_err)
{
	ft_putstr_fd("minishell: ", 2);
	if (command)
	{
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": ", 2);
	}
	if (detail)
		ft_putstr_fd(detail, 2);
	if (is_sys_err)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
	}
	ft_putstr_fd("\n", 2);
}