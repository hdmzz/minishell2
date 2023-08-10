#include "../../include/minishell.h"


static int	ft_mkstemp(char *filename)
{
	int	i;
	int	try_max;
	int	fd;

	i = 0;
	try_max = 0;
	fd = open(filename, O_CREAT | O_EXCL | O_RDWR | O_TRUNC, 0600);
	while (fd == -1 && try_max <= 15)
	{
		while (filename[i] && filename[i] != 'X')
			i++;
		if (filename[i] && ft_isalnum(filename[i] + 1))
			filename[i] = filename[i] + 1;
		else
			filename[i] = 97;
		fd = open(filename, O_CREAT | O_EXCL | O_RDWR | O_TRUNC, 0600);
		try_max++;
	}
	if (try_max == 15)
		return (-1);
	return (fd);
}

int	heredoc(char *delim, t_io *io)
{
	static char	tmpfile[] = "tmpfileXXXXXXXXXXXXXXX";
	int			fd;
	int			fdcpy;
	char		*input;
	char		*tmp;

	fd = ft_mkstemp(tmpfile);
	fdcpy = open(tmpfile, O_RDONLY, NULL);
	unlink(tmpfile);
	if (fd == -1)
		return (perror("Trop de fichier deja existant"), -1);
	while (1)
	{
 		input = readline("> ");
		if (ft_strcmp(delim, input) == 0)
			break ;
		tmp = heredoc_expanser(input, io);
		if (!tmp)
			return (free(input), 0);
		ft_putendl_fd(tmp, fd);//deja free ds here doc xpanser
		if (!io->var_expanser)
			free(tmp);
	}
	return (close(fd), io->delim_in_quotes = 0, fdcpy);
}
