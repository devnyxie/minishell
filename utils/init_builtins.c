/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:33:46 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/16 09:25:01 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int builtin_echo_wrapper(t_shell *shell, char **args)
{
    (void)shell;
    return builtin_echo(args);
}

static int builtin_pwd_wrapper(t_shell *shell, char **args)
{
    (void)shell;
    return builtin_pwd(args);
}

static int builtin_exit_wrapper(t_shell *shell, char **args)
{
    (void)shell;
    return exit_shell(args);
}

static int builtin_env_wrapper(t_shell *shell, char **args)
{
	(void)args;
	return builtin_env(shell);
}

t_builtin	*init_builtins_child(void)
{
	t_builtin	*builtins;

	builtins = malloc(4 * sizeof(t_builtin));
	if (!builtins)
		return (NULL);
	builtins[0] = (t_builtin){"echo", builtin_echo_wrapper};
	builtins[1] = (t_builtin){"pwd", builtin_pwd_wrapper};
	builtins[2] = (t_builtin){"env", builtin_env_wrapper};
	builtins[3] = (t_builtin){NULL, NULL};
	return (builtins);
}

t_builtin	*init_builtins_parent(void)
{
	t_builtin	*builtins;

	builtins = malloc(5 * sizeof(t_builtin));
	if (!builtins)
		return (NULL);
	builtins[0] = (t_builtin){"cd", builtin_cd};
	builtins[1] = (t_builtin){"export", builtin_export}; // TODO
	builtins[2] = (t_builtin){"unset", builtin_unset};  // TODO
	builtins[3] = (t_builtin){"exit", builtin_exit_wrapper};
	builtins[4] = (t_builtin){NULL, NULL};
	return (builtins);
}
