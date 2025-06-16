#include "../minishell.h"

static void	unset_env_var(char *name, t_shell *shell)
{
	int	i;
	int	j;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (shell->envp[i])
	{
		// try to find var to remove
		if (ft_strncmp(shell->envp[i], name, name_len) == 0 &&
			shell->envp[i][name_len] == '=')
		{
			free(shell->envp[i]);
			j = i;
			while (shell->envp[j])
			{
				shell->envp[j] = shell->envp[j + 1];
				j++;
			}
			// resize array;
		}
		i++;
	}
}

static int	is_valid_identifier(char *name)
{
	int	i;

	i = 0;
	if (!name || !*name)
	if (ft_isalnum(name[0]) == 0 && name[0] != '_')
		return (0);
	i++;
	while (name[i] && name[i] != '=')
	{
		if (ft_isalpha(name[i]) == 0 && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_unset(t_shell *shell, char **args)
{
	int	i;

	i = 1;

	if(args[1] == NULL)
	{
		printf("unset: not enough arguments\n");
		return (1);
	}

	// cmd->args[i]
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
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

