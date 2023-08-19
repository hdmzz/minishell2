#include "../../include/minishell.h"

int	left_redirections(t_cmd *cmds, int split_lght, t_shell *g_shell)
{
	int		i;
	int		fd;
	t_io	*io;
	char	**cmd;

	i = -1;
	io = g_shell->io;
	cmd = cmds->cmd;
	if (!cmd)
		return (1);
	while (++i < split_lght)
	{
		if (cmd[i][0] == '<')
		{
			if (ft_strcmp(cmd[i], "<<") == 0)
				fd = heredoc(cmd[i + 1], io);
			else
				fd = open(cmd[i + 1], O_RDONLY, NULL);
			if (fd == -1)
				return (0);
			cmds->input_backup = dup(STDIN_FILENO);
			dup2(fd, STDIN_FILENO);
			close(fd);
			cmd[i] = NULL;
			cmd[i + 1] = NULL;
			i++;
		}
	}
	return (1);
}
