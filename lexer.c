/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:08:35 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/03 17:40:17 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		// maybe change with ft_strcmp
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