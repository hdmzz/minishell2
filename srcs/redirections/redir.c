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
//ici on execute
int	redirections(t_shell *g_shell)
{
	t_cmd	*cmds;

	cmds = g_shell->cmds;
	while (cmds)//deplacer le while 
	{
		//isole ca pour chaque commande
		//on va faire les redir etc 
		right_redirections(cmds->cmd, split_lenght(cmds->cmd));
		left_redirections(cmds->cmd, split_lenght(cmds->cmd), g_shell);
		//---------------------------------------------
		//ci dessous on peut enlever et laisser ca a la fonction pipes qui execute les commandes
		if (!cmd_handler(g_shell))
			return (0);
		cmds = cmds->next;
	}
	//on fera ca apres 
	if (!recover_fd(g_shell))
		return (0);
	return (1);
}
