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
				ft_free_ptr(pipes[i]);
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
		dup2(cmds->fd_in, STDIN_FILENO);
	if (i != g_shell->nb_pipes)
		dup2(cmds->fd_out, STDOUT_FILENO);
	close_fds(pipes, g_shell->nb_pipes, -1);
	exec_cmd(cmds->cmd, cmds);
}

static void	free_pipes(t_shell *g_shell)
{
	int	i;

	i = -1;
	if (g_shell->pipes_fd != NULL)
	{
		while (++i < g_shell->nb_pipes)
			ft_free_ptr(g_shell->pipes_fd[i]);
		ft_free_ptr(g_shell->pipes_fd);
	}
}

void	restore_io(t_cmd *cmds)
{
	if (cmds->output_backup != -1)
		dup2(cmds->output_backup, STDOUT_FILENO);
	if (cmds->input_backup != -1)
		dup2(cmds->input_backup, STDIN_FILENO);
}

/* 
	Handle pipes 
	1. 
 */
int	handle_pipes_cmd(t_shell *g_shell)
{
	t_cmd	*cmds;
	int		i;
	int		ret;

	i = 0;
	cmds = g_shell->cmds;
	while (i < g_shell->nb_cmds)
	{
		left_redirections(cmds, split_lenght(cmds->cmd), g_shell);
		right_redirections(cmds, split_lenght(cmds->cmd));
		ret = dispatcher_builtin(g_shell, cmds);
		recover_or_io(cmds);
		if (ret == 0)
		{
			cmds->full_cmd_path = get_cmd_path(cmds->cmd);
			g_shell->pids[i] = fork();
			if (g_shell->pids[i] < 0)
				return (0);
			if (g_shell->pids[i] == 0)
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

//For each command determine the input and output
void	prepare_pipes_for_exec(t_shell *g_shell)
{
	t_cmd	*cmds;
	int		**pipes;
	int		i;

	i = 0;
	pipes = NULL;
	cmds = g_shell->cmds;
	if (g_shell->nb_cmds > 1)
		g_shell->pipes_fd = init_pipes(pipes, g_shell);
	g_shell->pids = ft_calloc(g_shell->nb_cmds, sizeof(pid_t));//peut etre alloc deux fois

//ici chaque commande sait dans quelle fd rediriger son output et son input

	while (i < g_shell->nb_cmds)
	{
		if (i > 0)
			cmds->fd_in = g_shell->pipes_fd[i - 1][0];
		if (i != g_shell->nb_cmds - 1)
			cmds->fd_out = g_shell->pipes_fd[i][1];
		cmds = cmds->next;
		i++;
	}

//--------------------------------------------------------------------------
}

/* 
	This function takes the cmds and execute it with the pipes etc
 */
int	cmd_handler(t_shell *g_shell)
{
	prepare_pipes_for_exec(g_shell);
	handle_pipes_cmd(g_shell);
	return (1);
}
