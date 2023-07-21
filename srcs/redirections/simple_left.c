#include "../../include/minishell.h"

int	simple_left(char **cmd, t_shell *g_shell)
{
	int	i;
	int	fd;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i][0] == '<')
		{
			g_shell->input_backup = dup(STDIN_FILENO);
			fd = open(cmd[i + 1], O_RDONLY, NULL);
			if (fd == -1)
				return (0);
			if (dup2(fd, STDIN_FILENO) == -1)//stdin est redirige vers le fichier
				return (0);
			close(fd);
		}
	}
	return (1);
}

//int main() {
//    FILE *file;
//    char buffer[100];

//    // Ouvrir le fichier en lecture
//    file = fopen("input.txt", "r");

//    if (file == NULL) {
//        printf("Impossible d'ouvrir le fichier.\n");
//        return 1;
//    }

//    // Rediriger l'entrée standard vers le fichier
//    freopen("input.txt", "r", stdin);

//    // Lire l'entrée du fichier ligne par ligne
//    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
//        printf("%s", buffer); // Afficher chaque ligne
//    }

//    // Fermer le fichier
//    fclose(file);

//    return 0;
//}
