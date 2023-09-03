#include "typedef.h"
#include "minishell.h"

int	exit_builtin(t_shell *g_shell, int last_exit)
{
	if (last_exit == 1)
		printf("exit\n");
	ft_free_shell(g_shell, last_exit);
	rl_clear_history();
	exit(last_exit);
}
