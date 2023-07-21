#include "../../include/minishell.h"

/* 
	pour recupper la commande si il y a une redirection
	il va falloir recuperer le mot apres la redir, faire la redirection,
	puis enlever le metacharactere et le mot qui represente le nom du fichier
	simple right == '>'
 */
int	simple_right(char **cmd, t_shell *g_shell)
{
	int	i;
	int	fd;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i][0] == '>')
		{
			g_shell->output_backup = dup(STDOUT_FILENO);
			fd = open(cmd[i + 1], 01101, S_IRUSR | S_IWUSR);
			if (fd == -1)
				return (-1);
			if (dup2(fd, STDOUT_FILENO) == -1)//maintenant ecrire sur stdout revient a ecrire sur fd
				return (-1);
			close(fd);
		}
	}
	return (1);
}
//pas fini il faut encore executer apres avoir rediriger peut etre avec un nvx
//process??
