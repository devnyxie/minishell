#include "../minishell.h"





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

