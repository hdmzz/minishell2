#include "../../include/minishell.h"

/* 
	pour recupper la commande si il y a une redirection
	il va falloir recuperer le mot apres la redir, faire la redirection,
	puis enlever le metacharactere et le mot qui represente le nom du fichier
 */

int	treat_cmd(char **cmd)
{
	int	i;
	int	redirection_pos;
	int	fd;
	int	saved_stdout;

	i = -1;
	saved_stdout = dup(STDOUT_FILENO);
	while (cmd[++i])
	{
		if (cmd[i][0] == '>')
		{
			redirection_pos = i;
			fd = open(cmd[i + 1], 01101, S_IRUSR | S_IWUSR);
			if (fd == -1)
				return 0;
			if (dup2(fd, STDOUT_FILENO) == -1)//maintenant ecrire sur stdout revient a ecrire sur fd
				return 0;
		}
	}
	while (redirection_pos != i)
	{
		free(cmd[redirection_pos]);
		cmd[redirection_pos] = NULL;
		redirection_pos++;
	}
	printf ("ici\n");
	print_cmd(cmd);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		return (perror("Erreur restauration sortie standard"), 0);
	close(fd);
	return (1);
}

int	simple_right_redirection(char *file_output)
{
	int	fd;
	int	saved_stdout;

	fd = open(file_output, 01101, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (perror("Erreur ouverture ficher"), 0);
	saved_stdout = dup(STDOUT_FILENO);
	if (dup2(fd, STDOUT_FILENO) == -1)//maintenant ecrire sur stdout revient a ecrire sur fd
		return (perror("Erreur redirection de la sortie standard"), 0);
	printf("hello test\n");
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		return (perror("Erreur restauration sortie standard"), 0);
	close(fd);
	return (1);
}

//int main() {
//    int fileDescriptor = open("output.txt", 01101, S_IRUSR | S_IWUSR);
//    if (fileDescriptor == -1) {
//        perror("Erreur lors de l'ouverture du fichier");
//        return 1;
//    }

//    // Sauvegarde le descripteur de fichier de la sortie standard
//    int savedStdout = dup(STDOUT_FILENO);

//    // Redirige la sortie standard vers le fichier
//    if (dup2(fileDescriptor, STDOUT_FILENO) == -1) {
//        perror("Erreur lors de la redirection de la sortie standard");
//        return 1;
//    }

//    // Écriture de la sortie dans le fichier
//    printf("Ceci est un exemple de redirection de la sortie standard vers un fichier.\n");

//    // Restaure le descripteur de fichier de la sortie standard
//    if (dup2(savedStdout, STDOUT_FILENO) == -1) {
//        perror("Erreur lors de la restauration de la sortie standard");
//        return 1;
//    }

//    // Fermeture du fichier
//    close(fileDescriptor);

//    return 0;
//}
