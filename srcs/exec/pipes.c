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

void	create_pipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("Erreur lors de la création du pipe");
		exit(EXIT_FAILURE);
	}
}

static void	error_free_pipes(t_cmd *c, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		c->pipes_fd = ft_free_ptr(c->pipes_fd);
		j++;
		c = c->next;
	}
}


static int	init_pipes(t_cmd *c, t_shell *g_shell)
{
	int	i;
	int	y;

	i = 0;
	while (i < g_shell->nb_pipes)
	{
		c->pipes_fd = ft_calloc(g_shell->nb_pipes, sizeof(int *));
		if (c->pipes_fd == NULL)
			{
				error_free_pipes(c, i);
				return (0);
			}
		create_pipe(c->pipes_fd[i]);
		i++;
		c = c->next;
	}
	//each command knows the next and the previous command and has access to the pipe
	return (1);
}

void	redir_io(t_cmd *c, t_shell *g_shell)
{
	if (c->fd_in != -1)
	{
		c->input_backup = dup(STDIN_FILENO);
		dup2(c->fd_in, STDIN_FILENO);
	}
	if (c->fd_out != -1)
	{
		c->output_backup = dup(STDOUT_FILENO);
		dup2(c->fd_out, STDOUT_FILENO);
	}
}

static void	child(t_cmd *cmds, t_shell *g_shell, int i)
{
	redir_io(cmds, g_shell, i);
	exec_cmd(cmds->cmd, cmds, g_shell);
}

static void	free_pipes(t_shell *g_shell)
{
	int	i;

	i = -1;
	if (g_shell->pipes_fd != NULL)
	{
		while (++i < g_shell->nb_pipes)
			ft_free_ptr(g_shell->pipes_fd[i]);
		g_shell->pipes_fd = ft_free_ptr(g_shell->pipes_fd);
	}
}

void	restore_io(t_cmd *cmds)
{
	if (cmds->output_backup != -1)
	{
		dup2(cmds->output_backup, STDOUT_FILENO);
		close(cmds->output_backup);
		cmds->output_backup = -1;
	}
	if (cmds->input_backup != -1)
	{
		dup2(cmds->input_backup, STDIN_FILENO);
		close(cmds->input_backup);
		cmds->output_backup = -1;
	}
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
		g_shell->pids[i] = fork();
		if (g_shell->pids[i] < 0)
			return (0);
		if (g_shell->pids[i] == 0)
			child(cmds, g_shell, i);
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
int	prepare_pipes_for_exec(t_shell *g_shell)
{
	t_cmd	*cmds;
	int		i;

	i = 0;
	cmds = g_shell->cmds;
	if (g_shell->nb_cmds > 1)
		init_pipes(cmds, g_shell);
	g_shell->pids = ft_calloc(g_shell->nb_cmds, sizeof(pid_t));
	if (g_shell->pids == NULL)
		return (0);
	return (1);
}


int	handle_cmd(t_shell *g_shell)
{
	t_cmd	*c;
	int		ret;

	c = g_shell->cmds;
	left_redirections(c, split_lenght(c->cmd), g_shell);
	right_redirections(c, split_lenght(c->cmd));
	ret = dispatcher_builtin(g_shell, c, );
	restore_io(c);
	return (ret);
}


/* 
	This function takes the cmds and execute it with the pipes etc
 */
int	cmd_handler(t_shell *g_shell)
{
	if (g_shell->nb_cmds == 1)
		return(handle_cmd(g_shell));
	else
	{
		prepare_pipes_for_exec(g_shell);
		return(handle_pipes_cmd(g_shell));
	}
	return (1);
}
