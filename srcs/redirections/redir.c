#include "../../include/minishell.h"

void	clean_cmd_tab(char **cmd, int first_redir, int end)
{
	while (first_redir && first_redir != end)
	{
		free(cmd[first_redir]);
		cmd[first_redir] = NULL;
		first_redir++;
	}
}

int	recover_fd(t_shell *g_shell)
{
	int	ret;

	ret = 1;
	if (g_shell->output_backup != -1)
	{
		if (dup2(g_shell->output_backup, STDOUT_FILENO) == -1)
			ret = 0;
	}
	if (g_shell->input_backup != -1)
	{
		if (dup2(g_shell->input_backup, STDIN_FILENO) == -1)
			ret = 0;
	}
	return (ret);
}
