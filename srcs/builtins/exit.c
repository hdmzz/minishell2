#include "typedef.h"
#include "minishell.h"

int	exit_builtin(t_shell *g_shell)
{
	printf("exit\n");
	//close_fds(g_shell->pipes_fd, g_shell->nb_pipes, -1);
	ft_free_shell(g_shell, 1);
	exit(g_last_exit_code);
	return (0);
}
