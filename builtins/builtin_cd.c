/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafanasi <tafanasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:00:01 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/08/22 11:08:41 by tafanasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*cd_resolve_target(t_shell *shell, char **args)
{
	if (!args || !args[1] || *args[1] == '~')
		return (get_env_var(shell, "HOME"));
	return (args[1]);
}

static void	update_pwd_after_chdir(t_shell *shell)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;

	old_pwd = get_env_var(shell, "PWD");
	if (old_pwd)
		update_env_var(shell, "OLDPWD", old_pwd);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		update_env_var(shell, "PWD", cwd);
	else
		report_error("getcwd", NULL, 1);
}

int	builtin_cd(t_shell *shell, char **args)
{
	char	*path;

	if (!shell || !args)
		return (1);
	path = cd_resolve_target(shell, args);
	if (!path)
		exit(EXIT_FAILURE);
	if (chdir(path) == -1)
	{
		report_error("cd", path, 1);
		return (1);
	}
	update_pwd_after_chdir(shell);
	return (0);
}
