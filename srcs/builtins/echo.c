#include "minishell.h"

int	echo_builtin(char **args, t_shell *g_shell)
{
	int i;

	i = 1;
	while (args[i])
	{
		ft_putstr(args[i]);
		ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}
