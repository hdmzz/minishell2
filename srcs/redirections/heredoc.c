#include "../../include/minishell.h"

//void heredoc(char* delimiter) 
//{
//    char buffer[1024];
//    FILE* temp_file = tmpfile(); 
//    if (temp_file == NULL) {
//        perror("Erreur lors de la création du fichier temporaire");
//        exit(EXIT_FAILURE);
//    }

//    while (1) {
//		//
//        if (fgets(buffer, 1024, stdin) == NULL) {
//            // Si fgets retourne NULL, cela signifie qu'il n'
//            // Nous arrêtons donc la boucle.
//            break;
//        }

//        // Vérifier si la ligne correspond au délimiteur
//        if (strcmp(buffer, delimiter) == 0) {
//            break;
//        }

//        // Écrire la ligne dans le fichier temporaire
//        fputs(buffer, temp_file);
//    }

//    // Repositionner le curseur du fichier temporaire au début
//    rewind(temp_file);

//    // Lire le contenu du fichier temporaire et l'afficher sur stdout
//    while (fgets(buffer, 1024, temp_file) != NULL) {
//        printf("%s", buffer);
//    }

//    // Fermer le fichier temporaire
//    fclose(temp_file);
//}


//je dois implementer une fonction qui ouvre un fichier unique
// et renvoie son fd

static int	ft_mkstemp(char *filename)
{
	int	i;
	int	try_max;
	int	fd;

	i = 0;
	try_max = 0;
	fd = open(filename, O_CREAT | O_EXCL | O_RDWR, S_IWUSR | S_IRUSR);
	while (fd == -1 && try_max <= 15)
	{
		while (filename[i] && filename[i] != 'X')
			i++;
		if (filename[i] && ft_isalnum(filename[i] + 1))
			filename[i] = filename[i] + 1;
		else
			filename[i] = 97;
		fd = open(filename, O_CREAT | O_EXCL | O_RDWR, S_IWUSR | S_IRUSR);
		try_max++;
	}
	if (try_max == 15)
		return (-1);
	return (fd);
}

//pour creer un ficier temporaire
FILE* tmpfile(void)
{
    char filename[] = "tmpfileXXXXXXXXXXXXXXX";//15 X
    FILE* file;
    int fd;

    // Créer le fichier temporaire avec le modèle de nom spécifié
    fd = mkstemp(filename);
    if (fd == -1) {
        perror("Erreur lors de la création du fichier temporaire");
        return NULL;
    }

    // Ouvrir le fichier temporaire en mode binaire (lecture et écriture)
    file = fdopen(fd, "w+b");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier temporaire");
        return NULL;
    }

    // Supprimer immédiatement le fichier du système de fichiers (il sera toujours accessible via le FILE* file)
    unlink(filename);

    return file;
}

void	read_the_file(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
}

void	heredoc(char *delim)
{
	static	char tmpfile[] = "tmpfileXXXXXXXXXXXXXXX";
	int		fd;
	char	*input;

	fd = ft_mkstemp(tmpfile);
	if (fd == -1)
	{
		perror("Trop de fichier deja existant");
		return ;
	}
	unlink(tmpfile);
	while (1)
	{
		input = get_next_line(STDIN_FILENO);
		if (input == NULL)
			break ;
		if (strncmp(delim, input, ft_strlen(delim)) == 0)
			break ;
		ft_putstr_fd(input, fd);
		free(input);
	}
	read_the_file(fd);
	close(fd);
}

