#include "minishell.h"

void	close_fds(int **fds, int nb_pipes, int i)
{
	int	j;

	j = 0;
	if (i != -1)
	{
		while (j < nb_pipes)
		{
			if (j != i && j != i + 1)
			{
				close(fds[j][0]);
				close(fds[j][1]);
			}
			j++;
		}
	}
	if (i == -1)
	{
		while (++i < nb_pipes)
		{
			close(fds[i][0]);
			close(fds[i][1]);
		}
	}
}

void	simple_close(int **fds, int i)
{
	close(fds[i][0]);
	close(fds[i][1]);
}

void	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("Erreur lors de la création du pipe");
		exit(EXIT_FAILURE);
	}
}

static int	**init_pipes(int **pipes, t_shell *g_shell)
{
	int	i;
	int	j;

	j = -1;
	i = -1;
	pipes = ft_calloc(g_shell->nb_pipes, sizeof(int *));
	if (pipes == NULL)
		return(perror("pipes init"), NULL);
	while (++i < g_shell->nb_pipes)
	{
		pipes[i] = ft_calloc(2, sizeof(int));
		if (pipes[i] == NULL)
		{
			while (++j <= i)
				free(pipes[i]);
			return (0);
		}
	}
	i = -1;
	while (++i < g_shell->nb_pipes)
		pipe(pipes[i]);
	return (pipes);
}

static void	child(t_cmd *cmds, t_shell *g_shell, int i)
{
	int	**pipes;

	pipes = g_shell->pipes_fd;
	if (i != 0)
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
	}
	if (i != g_shell->nb_pipes)
	{
		dup2(pipes[i][1], STDOUT_FILENO);
	}
	close_fds(pipes, g_shell->nb_pipes, -1);
	exec_cmd(cmds->cmd, g_shell);
}

static void	free_pipes(t_shell *g_shell)
{
	int	i;

	i = -1;
	if (g_shell->pipes_fd != NULL)
	{
		while (++i < g_shell->nb_pipes)
			free(g_shell->pipes_fd[i]);
		free(g_shell->pipes_fd);
	}
}

/* 
	Handle pipes 
 */
int	handle_pipes_cmd(t_shell *g_shell)
{
	int		**pipes;
	t_cmd	*cmds;
	int		i;

	i = 0;
	pipes = NULL;
	cmds = g_shell->cmds;
	g_shell->pids = ft_calloc(g_shell->nb_cmds, sizeof(pid_t));
	g_shell->pipes_fd = init_pipes(pipes, g_shell);//to free
	while (i < g_shell->nb_cmds)
	{
		if (g_shell->full_cmd_path != NULL)
			free(g_shell->full_cmd_path);
		g_shell->full_cmd_path = get_cmd_path(cmds->cmd);
		g_shell->pids[i] = fork();
		if (g_shell->pids[i] < 0)
			return (0);
		if (g_shell->pids[i] == 0)
		{
			left_redirections(cmds->cmd, split_lenght(cmds->cmd), g_shell);
			right_redirections(cmds->cmd, split_lenght(cmds->cmd));
			child(cmds, g_shell, i);
		}
		i++;
		cmds = cmds->next;
	}
	close_fds(g_shell->pipes_fd, g_shell->nb_pipes, -1);
	i = -1;
	while (++i < g_shell->nb_cmds)
		waitpid(g_shell->pids[i], &g_last_exit_code, 0);
	free_pipes(g_shell);
	return (1);
}

int	handle_cmd(t_shell *g_shell)
{
	pid_t	pid;

	g_shell->full_cmd_path = get_cmd_path(g_shell->cmds->cmd);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		left_redirections(g_shell->cmds->cmd, split_lenght(g_shell->cmds->cmd), g_shell);
		right_redirections(g_shell->cmds->cmd, split_lenght(g_shell->cmds->cmd));
		exec_cmd(g_shell->cmds->cmd, g_shell);
	}
	waitpid(pid, &g_last_exit_code, 0);
	free(g_shell->full_cmd_path);
	g_shell->full_cmd_path = NULL;
	return (1);
}

/* 
	This function takes the cmds and execute it with the pipes etc
 */
int	cmd_handler(t_shell *g_shell)
{
	if (g_shell->nb_cmds == 1)
		handle_cmd(g_shell);
	else
		handle_pipes_cmd(g_shell);
	return (1);
}
