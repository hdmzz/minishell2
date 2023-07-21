#include "../../include/minishell.h"

int	simple_left(char **cmd)//on redirige
{
	int	i;
	int	first_redir;;
	int	fd;
	int	saved_stdin;

	i = -1;
	first_redir = 0;
	saved_stdin = dup(STDIN_FILENO);
	while (cmd[++i])
	{
		if (cmd[i][0] == '<')
			if (first_redir == 0)
				first_redir = i;
		fd = open(cmd[i + 1], O_RDONLY, NULL);
		if (fd == -1)
			return (0);
		if (dup2(fd, STDIN_FILENO) == -1)//stdin est redirige vers le fichier
			return (0);
	}
	close(fd);
	
	return (saved_stdin);
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
