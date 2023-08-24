#include "minishell.h"

int	env_builtin(char **cmd, t_shell *g_shell)
{
	int	i;

	i = 0;
	if (split_lenght(cmd) > 1)
		return (0);
	if (g_shell->split_env == NULL)
		return (0);
	while (g_shell->split_env[i])
	{
		printf("%s\n", g_shell->split_env[i]);
		i++;
	}
	return (1);
}
