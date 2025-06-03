/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:33:46 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/03 17:36:23 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_builtin	*init_builtins(void)
{
	t_builtin	*g_builtins;

	g_builtins = malloc((3 + 1) * sizeof(t_builtin));
	if (!g_builtins)
		return (NULL);
	g_builtins[0].name = "exit";
	g_builtins[0].fn = &exit_shell;
	g_builtins[1].name = "echo";
	g_builtins[1].fn = &builtin_echo;
	g_builtins[2].name = "pwd";
	g_builtins[2].fn = &builtin_pwd;
	g_builtins[3].name = NULL;
	g_builtins[3].fn = NULL;
	return (g_builtins);
}
