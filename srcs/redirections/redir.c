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
