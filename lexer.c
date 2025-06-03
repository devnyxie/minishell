/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:08:35 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/03 18:12:43 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// @accepts command and arguments : TODO
void	lexer(char *command, char **args)
{
	t_builtin *builtins;
	int i;

	i = 0;
	builtins = init_builtins();
	while (builtins[i].name != NULL)
	{
		// todo: maybe change with ft_strcmp
		if (ft_strncmp(command, builtins[i].name,
				ft_strlen(builtins[i].name)) == 0)
		{
			builtins[i].fn(args);
			return ;
		}
		i++;
	}
	if (builtins[i].name == NULL)
		printf("%s: command not found\n", command); //todo: external cmd check
	free(builtins);
	return ;
}