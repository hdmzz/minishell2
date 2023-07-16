#include "../../include/minishell.h"

int	simple_right_redirection(char *file_output)
{
	int	fd;
	int	saved_stdout;

	fd = open(file_output, 01101, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (perror("Erreur ouverture ficher"), 0);
	saved_stdout = dup(STDOUT_FILENO);
	if (dup2(fd, STDOUT_FILENO) == -1)
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
