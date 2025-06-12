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
	return (0);
}

