#include "../../include/minishell.h"

static void	error_free(int **tab, int i)
{
	while (i--)
		free(tab[i]);
	free(tab);
} 

static int	init_pipes_fd(int nb_cmds, int **pipes_fd)
{
	int	i;

	i = 0;
	pipes_fd = ft_calloc(nb_cmds - 1, sizeof(int *));
	if (pipes_fd == NULL)
		return (perror("Error calloc init pipes"), 0);
	while (i < nb_cmds - 1)
	{
		pipes_fd[i] = ft_calloc(2, sizeof(int));
		if (pipes_fd[i] == NULL || pipe(pipes_fd[i]) == -1)
			return (error_free(pipes_fd, i), 0);
		i++;
	}
	return (1);
}

int	pipe(t_shell *g_shell)
{
	int		nb_cmds;
	int		**pipes_fd;
	int		i;
	int		j;
	pid_t	pid;
	t_cmd	*cmds;

	nb_cmds = g_shell->nb_cmds;
	i = 0;
	cmds = g_shell->cmds;
	//ouverture des pipes du tableau et malloc
	//si une seule commande faudra penser a tout free etc
	if (!init_pipes_fd(nb_cmds, pipes_fd))
		return (perror("Error init pipes"), 0);
	//executer les commandes
	while (i < nb_cmds)
	{
		pid = fork();
		if (pid == -1)
			return(error_free(pipes_fd, nb_cmds - 1), 0);
		if (pid == 0)
		{
			if (i != 0)
				dup2(pipes_fd[i - 1][0], STDIN_FILENO);//entree processus enfant redirigee vers tete de lecture du pipe
			if (i != nb_cmds - 1)
				dup2(pipes_fd[i][1], STDOUT_FILENO);//sortie  processus enfant redirige vers tete d'ecriture du pipe
//il faut close les descripteurs des autres car la memoire est dupliquee lors dun fork donc il resteront ouvert si on les ferment pas
			j = 0;
			while (j < nb_cmds - 1)
			{
				if (j != i - 1 && i != i)
				{
					close(pipes_fd[j][0]);
					close(pipes_fd[j][1]);
				}
			}
			//il faut executer la  commande maintenant
			
			exec_cmd(cmds->cmd);
			//si erreur
			return (perror("Error commmande exec"), 0);
		}
		//ici process pere
		else if  (pid > 0)
		{
			//on libere les fds non utilisee
			j = 0;
			while (j < nb_cmds - 1)
			{
				close(pipes_fd[j][0]);
				close(pipes_fd[j][1]);
			}
			j++;
			while (j--)
				wait(NULL);
			while (j < nb_cmds - 1)
				free(pipes_fd[j]);
			free(pipes_fd);
			return (1);
		}
		
	}

}
