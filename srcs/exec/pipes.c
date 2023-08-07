#include "../../include/minishell.h"

static void	close_fds(int **fds, int nb_pipes, int i)
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
/* 
	This function must close the inutilized fds

 */
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
		//i = 0 pour premiere commande nb pipes = 1 ds notre cas
		dup2(pipes[i][1], STDOUT_FILENO);
	}
	close_fds(pipes, g_shell->nb_pipes, -1);
	exec_cmd(cmds->cmd, g_shell);
}
/* 
	Handle pipes 
 */
int	handle_pipes_cmd(t_shell *g_shell)
{
	int		**pipes;
	t_cmd	*cmds;
	int		i;
	int		pid;

	i = 0;
	pipes = NULL;
	cmds = g_shell->cmds;
	g_shell->pipes_fd = init_pipes(pipes, g_shell);
	while (i < g_shell->nb_cmds)
	{
		pid = fork();

		//int y;
		//scanf("%d", &y);

		if (pid < 0)
			return (0);
		if (pid == 0)
			child(cmds, g_shell, i);
		i++;
		cmds = cmds->next;
	}
	close_fds(g_shell->pipes_fd, g_shell->nb_pipes, -1);
	i = -1;
	while (++i < g_shell->nb_cmds)
		wait(NULL);
	return (1);
}

int	handle_cmd(t_shell *g_shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		exec_cmd(g_shell->cmds->cmd, g_shell);
	wait(NULL);
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
