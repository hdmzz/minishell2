#include "../../include/minishell.h"

/* 
	pour recupper la commande si il y a une redirection
	il va falloir recuperer le mot apres la redir, faire la redirection,
	puis enlever le metacharactere et le mot qui represente le nom du fichier
	simple right == '>'
	01101 == O_WRONLY | O_CREAT | O_TRUNC
	pour >> il faudrait O_WRONLY | O_APPEND | O_CREAT
 */
int	right_redirections(char **cmd)
{
	int		i;
	int		fd;
	int		split_lght;
	int		oflag;

	i = 0;
	split_lght = split_lenght(cmd);
	oflag = O_WRONLY | O_CREAT | O_TRUNC;
	while (i < split_lght)
	{
		if (cmd[i][0] == '>' && ft_strlen(cmd[i]) <= 2)
		{
			if (!ft_strncmp(cmd[i], ">>", 2))
				oflag = O_WRONLY | O_APPEND | O_CREAT;
			fd = open(cmd[i + 1], oflag, 0644);
			if (fd == -1)
				return (-1);
			if (dup2(fd, STDOUT_FILENO) == -1)//maintenant ecrire sur stdout revient a ecrire sur fd
				return (-1);
			close(fd);
			cmd[i] = NULL;
			cmd[i + 1] = NULL;
			i++;
		}
		i++;
	}
	return (1);
}
