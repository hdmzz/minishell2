#include "minishell.h"

static void	child(int pipe_fd[2], char *full_cmd_path, char **cmd_tab)
{
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execve(full_cmd_path, cmd_tab, NULL);
	perror("exec pipes");
	exit(1);
}

//une fonction qui lis une ligne apres l'autre le fd du fichier passé en parametre stock chaque ligne dans un buffer et renvoie le buffer
static char	*recompose_output(int fd, ssize_t bytes_read)
{
	char	*buffer;
	char	*tmp;
	char	*line;

	buffer = ft_calloc(1024, sizeof(char));
	if (!buffer)
		return (NULL);
	line = ft_calloc(1024, sizeof(char));
	if (!line)
		return (NULL);
	while (1)
	{
		bytes_read = read(fd, line, 1024 - 1);
		if (bytes_read == -1)
			return (NULL);
		if (bytes_read == 0)
			break ;
		line[bytes_read] = '\0';
		tmp = ft_strjoin(buffer, line);
		ft_free_ptr(buffer);
		buffer = tmp;
	}
	ft_free_ptr(line);
	return (buffer);
}

char	*exec_imbricated_cmd(char *cmd_str, ssize_t bytes_read)
{
	char	**cmd_tab;
	int		pid;
	int		pipe_fd[2];
	char	*output;
	char	*full_cmd_path;

	cmd_tab = ft_split(cmd_str, 32);
	full_cmd_path = get_cmd_path(cmd_tab);
	if (full_cmd_path == NULL)
		return (printf("bash: command not found\n"), NULL);
	if (pipe(pipe_fd) == -1)
		perror("Pipe\n");
	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
		child(pipe_fd, full_cmd_path, cmd_tab);
	close(pipe_fd[1]);
	output = recompose_output(pipe_fd[0], bytes_read);
	close (pipe_fd[0]);
	if (output == NULL)
		return (NULL);
	waitpid(pid, &g_last_exit_code, 0);
	ft_free_ptr(full_cmd_path);
	return (output);
}
