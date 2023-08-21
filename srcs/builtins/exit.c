#include "typedef.h"
#include "minishell.h"

int	exit_builtin(t_shell *g_shell, int last_exit)
{
	printf("exit\n");
	ft_free_shell(g_shell, last_exit);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
