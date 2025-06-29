/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:12:12 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/29 12:42:38 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	custom_error(char *msg)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	printf("%s\n", msg);
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