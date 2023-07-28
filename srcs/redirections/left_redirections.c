#include "../../include/minishell.h"

//le but est d'isoler la redirections ds une fonction 
int	redir_input(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
		return (0);
	return (1);
}

int	left_redirections(char **cmd, int split_lght)
{
	int		i;
	int		fd;

	i = -1;
	if (!cmd)
		return (1);
	while (++i < split_lght)
		if (cmd[i][0] == '<')
		{
			if (strncmp(cmd[i], "<<", ft_strlen(cmd[i])) == 0)
				fd = heredoc(cmd[i + 1]);
			else
				fd = open(cmd[i + 1], O_RDONLY, NULL);
			if (fd == -1)
				return (0);
			redir_input(fd);
			close(fd);
			cmd[i] = NULL;
			cmd[i + 1] = NULL;
			i++;
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
