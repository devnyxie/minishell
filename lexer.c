/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:08:35 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/02 12:59:12 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin	*init_builtins(void)
{
	t_builtin	*g_builtins;

	g_builtins = malloc(4 * sizeof(t_builtin));
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

// static void lexer_external(){}

// @accepts command and arguments : TODO
// only builtins for now
void	lexer(char *command, char **args)
{
	t_builtin *builtins;
	int i;

	i = 0;
	builtins = init_builtins();
	while (builtins[i].name != NULL)
	{
		if (builtins[i].name == NULL)
			break ;
		// maybe change with ft_strcmp
		if (ft_strncmp(command, builtins[i].name,
				ft_strlen(builtins[i].name)) == 0)
		{
			builtins[i].fn(args);
			return ;
		}
		i++;
	}
	free(builtins);
	return ;
}