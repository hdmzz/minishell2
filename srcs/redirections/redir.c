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
//!!!! WARNING pas encore les pipes!!!!!!
int	redirections(t_shell *g_shell)//genre de for each node in cmds
{
	t_cmd	*cmds;

	cmds = g_shell->cmds;
	while (cmds)
	{
		right_redirections(cmds->cmd);
		left_redirections(cmds->cmd);
		if (!exec_cmd(cmds->cmd))
			return (0);
		cmds = cmds->next;
	}
	//la commande a ete executee il faut remettre tout dans l'ordre maintenant
	if (!recover_fd(g_shell))
		return (0);
	return (1);
}
