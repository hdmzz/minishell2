#include "minishell.h"

int	env_builtin(char **cmd, t_shell *g_shell)
{
	int	i;

	i = 0;
	if (split_lenght(cmd) > 1)
		return (EXIT_FAILURE);
	if (g_shell->split_env == NULL)
		return (EXIT_FAILURE);
	while (g_shell->split_env[i])
	{
		printf("%s\n", g_shell->split_env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
