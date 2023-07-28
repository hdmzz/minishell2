#include "../../include/minishell.h"

//je dois implementer une fonction qui ouvre un fichier unique
// et renvoie son fd
static int	ft_mkstemp(char *filename)
{
	int	i;
	int	try_max;
	int	fd;

	i = 0;
	try_max = 0;
	fd = open(filename, O_CREAT | O_EXCL | O_RDWR | O_TRUNC, S_IWUSR | S_IRUSR);
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

int	heredoc(char *delim)
{
	static char	tmpfile[] = "tmpfileXXXXXXXXXXXXXXX";
	int			fd;
	int			fdcpy;
	char		*input;

	fd = ft_mkstemp(tmpfile);
	fdcpy = open(tmpfile, O_RDONLY, NULL);
	unlink(tmpfile);
	if (fd == -1)
		return (perror("Trop de fichier deja existant"), -1);
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			break ;
		if (ft_strncmp(delim, input, ft_strlen(input)) == 0)
			break ;
		ft_putendl_fd(input, fd);
		free(input);
	}
	if (input)
		free(input);
	ft_putendl_fd("", fd);
	close (fd);
	return (fdcpy);
}
