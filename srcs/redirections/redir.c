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

int	recover_fd(int saved_fd, int redir_type)
{
	int	std_in_out;

	std_in_out = STDIN_FILENO;//<
	if (redir_type == larger || redir_type == d_larger)//1 pour out, 0 pour in
		std_in_out = STDOUT_FILENO;
	if (dup2(saved_fd, std_in_out) == -1)
		return (perror("Erreur restauration std in/out"), 0);
	return (1);
}

int	redirections(t_shell *g_shell)//genre de for each node in cmds
{
	t_cmd	*cmds;
	int		i;
	int		y;
	int		saved_fd;

	cmds = g_shell->cmds;
	i = 0;
	while (cmds)
	{
		simple_left(cmds->cmd);
		cmds ++;
	}

}
