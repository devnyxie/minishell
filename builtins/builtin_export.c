/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:27:22 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/18 18:10:34 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	sort_env(t_shell *shell)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (i < shell->env_count - 1)
	{
		j = 0;
		while (j < shell->env_count - 1 - i)
		{
			if (ft_strcmp(shell->envp[j], shell->envp[j + 1]) > 0)
			{
				temp = shell->envp[j];
				shell->envp[j] = shell->envp[j + 1];
				shell->envp[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	build_env_var(t_shell *shell, char **args, int i)
{
	char	*equals;
	char	*detail_mgs;

	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			detail_mgs = ft_strjoin("`", args[i]);
			detail_mgs = ft_strjoin(detail_mgs, "': not valid identifier");
			report_error("export", detail_mgs, 0);
			free(detail_mgs);
			return ;
		}
		equals = ft_strchr(args[i], '=');
		if (equals)
		{
			*equals = '\0';
			update_env_var(shell, args[i], equals + 1);
			*equals = '=';
		}
		else
			update_env_var(shell, args[i], "");
		i++;
	}
}

int	builtin_export(t_shell *shell, char **args)
{
	int	i;

	i = 0;
	if (args[1] == NULL)
	{
		sort_env(shell);
		while (i < shell->env_count)
		{
			printf("declare -x %s\n", shell->envp[i]);
			i++;
		}
		return (0);
	}
	i = 1;
	build_env_var(shell, args, i);
	return (0);
}
