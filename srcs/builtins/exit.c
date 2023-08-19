#include "typedef.h"
#include "minishell.h"

int	exit_builtin(t_shell *g_shell)
{
	printf("exit\n");
	ft_free_shell(g_shell, 1);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
