#include "../../include/minishell.h"

void	clean_cmd_tab(char **cmd, int first_redir, int end)
{
	while (first_redir && first_redir != end)
	{
		ft_free_ptr(cmd[first_redir]);
		cmd[first_redir] = NULL;
		first_redir++;
	}
}

void	recover_or_io(t_cmd *cmd)
{
	if (cmd->output_backup != -1)
		dup2(cmd->output_backup, STDOUT_FILENO);
	if (cmd->input_backup != -1)
		dup2(cmd->input_backup, STDIN_FILENO);
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
