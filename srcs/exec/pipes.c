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
	pid_t	pid;

	nb_cmds = g_shell->nb_cmds;
	i = 0;
	if (!init_pipes_fd(nb_cmds, pipes_fd))
		return (perror("Error init pipes"), 0);
	//executer les commandes
	while (i < nb_cmds)
	{
		pid = fork();
		if (pid == -1)
			return(error_free(pipes_fd, nb_cmds - 1), 0);
		
	}

}

int main() {
    int num_commands = 3; // Modifier ce nombre selon le nombre de commandes que vous voulez exécuter
    char* commands[][3] = {
        {"ls", "-l", NULL},//value 
        {"grep", "file", NULL},
        {"wc", "-l", NULL}
    };

    // Allouer de l'espace pour le tableau des pipes
    int** pipes = (int**)malloc((num_commands - 1) * sizeof(int*));
    for (int i = 0; i < num_commands - 1; i++) {
        pipes[i] = (int*)malloc(2 * sizeof(int));
        if (pipe(pipes[i]) == -1) {
            perror("Erreur lors de la création des pipes");
            return 1;
        }
    }

    // Exécuter les commandes
    for (int i = 0; i < num_commands; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("Erreur lors de la création des processus enfants");
            return 1;
        } else if (pid == 0) {
            // Code du processus enfant

            // Rediriger l'entrée du processus enfant
            if (i != 0) {
                dup2(pipes[i - 1][0], STDIN_FILENO);
            }

            // Rediriger la sortie du processus enfant
            if (i != num_commands - 1) {
                dup2(pipes[i][1], STDOUT_FILENO);
            }

            // Fermer les descripteurs de fichiers des pipes non utilisés
            for (int j = 0; j < num_commands - 1; j++) {
                if (j != i - 1 && j != i) {
                    close(pipes[j][0]);
                    close(pipes[j][1]);
                }
            }

            // Exécuter la commande
            execvp(commands[i][0], commands[i]);

            // Cette ligne ne sera atteinte que si execvp échoue
            perror("Erreur lors de l'exécution de la commande");
            return 1;
        }
    }

    // Fermer les descripteurs de fichiers des pipes dans le processus père
    for (int i = 0; i < num_commands - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // Attendre que tous les processus enfants se terminent
    for (int i = 0; i < num_commands; i++) {
        wait(NULL);
    }

    // Libérer la mémoire allouée pour les pipes
    for (int i = 0; i < num_commands - 1; i++) {
        free(pipes[i]);
    }
    free(pipes);

    return 0;
}
