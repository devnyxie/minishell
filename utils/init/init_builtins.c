/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:33:46 by tafanasi          #+#    #+#             */
/*   Updated: 2025/08/08 11:59:52 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	builtin_echo_wrapper(t_shell *shell, char **args)
{
	(void)shell;
	return (builtin_echo(args));
}

static int	builtin_pwd_wrapper(t_shell *shell, char **args)
{
	(void)shell;
	return (builtin_pwd(args));
}

static int	builtin_exit_wrapper(t_shell *shell, char **args)
{
	free_shell(shell);
	clear_history();
	return (exit_shell(args));
}

t_builtin	*init_builtins_child(void)
{
	t_builtin	*builtins;

	builtins = malloc(2 * sizeof(t_builtin));
	if (!builtins)
		return (NULL);
	builtins[0] = (t_builtin){"env", builtin_env};
	builtins[1] = (t_builtin){NULL, NULL};
	return (builtins);
}

t_builtin	*init_builtins_parent(void)
{
	t_builtin	*builtins;

	builtins = malloc(7 * sizeof(t_builtin));
	if (!builtins)
		return (NULL);
	builtins[0] = (t_builtin){"cd", builtin_cd};
	builtins[1] = (t_builtin){"export", builtin_export};
	builtins[2] = (t_builtin){"unset", builtin_unset};
	builtins[3] = (t_builtin){"exit", builtin_exit_wrapper};
	builtins[4] = (t_builtin){"echo", builtin_echo_wrapper};
	builtins[5] = (t_builtin){"pwd", builtin_pwd_wrapper};
	builtins[6] = (t_builtin){NULL, NULL};
	return (builtins);
}
