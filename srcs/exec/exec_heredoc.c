/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:16:36 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/06 01:34:50 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(int pipe_fd[2], char *full_cmd_path, char **cmd_tab)
{
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execve(full_cmd_path, cmd_tab, NULL);
	perror("exec pipes child heredoc");
	exit(1);
}

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

char	*exec_imbricated_cmd(char *cmd_str, ssize_t bytes_read, t_shell *g)
{
	char	**cmd_tab;
	int		pid;
	int		pipe_fd[2];
	char	*output;
	char	*full_cmd_path;

	cmd_tab = ft_split(cmd_str, 32);
	full_cmd_path = get_cmd_path(cmd_tab, g);
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
	return (ft_free_split(cmd_tab), output);
}
