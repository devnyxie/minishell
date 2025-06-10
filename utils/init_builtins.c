/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:33:46 by tafanasi          #+#    #+#             */
/*   Updated: 2025/06/10 10:44:32 by mmitkovi         ###   ########.fr       */
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

t_builtin	*init_builtins(void)
{
	t_builtin	*builtins;

	builtins = malloc(8 * sizeof(t_builtin));
	if (!builtins)
		return (NULL);
	builtins[0] = (t_builtin){"echo", builtin_echo_wrapper};
	builtins[1] = (t_builtin){"cd", builtin_cd};
	builtins[2] = (t_builtin){"pwd", builtin_pwd_wrapper};
	builtins[3] = (t_builtin){"export", NULL}; // TODO
	builtins[4] = (t_builtin){"unset", NULL};  // TODO
	builtins[5] = (t_builtin){"env", builtin_env_wrapper};
	builtins[6] = (t_builtin){"exit", builtin_exit_wrapper};
	builtins[7] = (t_builtin){NULL, NULL};
	return (builtins);
}
