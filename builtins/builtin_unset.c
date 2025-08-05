/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:10:39 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/05 10:35:08 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_unset(t_shell *shell, char **args)
{
	int	i;

	i = 1;
	if (args[1] == NULL)
	{
		printf("unset: not enough arguments\n");
		return (1);
	}
	while (args[i])
	{
		if (!is_valid_identifier(args[i]) || ft_strchr(args[i], '=') != NULL)
		{
			printf("unset: `%s': not a valid identifier\n", args[i]);
			return (1);
		}
		else
			unset_env_var(args[i], shell);
		i++;
	}
	return (0);
}
