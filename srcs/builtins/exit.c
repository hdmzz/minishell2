#include "typedef.h"
#include "minishell.h"

int	exit_builtin(t_shell *g_shell)
{
	printf("exit\n");
	ft_free_shell(g_shell, 1);
	exit(g_last_exit_code);
	return (0);
}