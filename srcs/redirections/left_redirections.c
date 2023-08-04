#include "../../include/minishell.h"

//le but est d'isoler la redirections ds une fonction 
//1  = output
//0 = in
int	redir_in_or_out(int fd, int in_or_out)
{
	if (dup2(fd, in_or_out) == -1)
		return (0);
	return (1);
}

int	left_redirections(char **cmd, int split_lght, t_io *io)
{
	int		i;
	int		fd;

	i = -1;
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
			redir_in_or_out(fd, STDIN_FILENO);
			close(fd);
			cmd[i] = NULL;
			cmd[i + 1] = NULL;
			i++;
		}
	}
	return (1);
}
