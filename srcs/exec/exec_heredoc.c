#include "../../include/minishell.h"

char	*pipe_heredoc(char *cmd_str)
{
	char	**cmd_tab;
	int		pid;
	int		pipe_fd[2];
	char	 *buffer;
	ssize_t	bytes_read;
	char	*full_cmd_path;

	cmd_tab = ft_split(cmd_str, 32);
	full_cmd_path = get_cmd_path(cmd_tab);
	buffer = ft_calloc(1024, sizeof(char));
	if (!buffer)
		return (NULL);
	if (pipe(pipe_fd) == -1)
		perror("Pipe\n");
	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		redir_in_or_out(pipe_fd[1], STDOUT_FILENO);
		execve(full_cmd_path, cmd_tab, NULL);
		return (perror("Exec pipe"), NULL);
	}
	else
	{
		close(pipe_fd[1]);
		bytes_read = read(pipe_fd[0], buffer, 1024 - 1);
		if (bytes_read == -1)
			return (NULL);
		buffer[bytes_read] = '\0';
		waitpid(pid, NULL, 0);
		return (buffer);
	}
	return (NULL);
}
