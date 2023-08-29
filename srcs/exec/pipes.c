/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 01:54:22 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/29 11:19:35 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(int *fd)
{
	if (fd != NULL)
	{
		close(fd[1]);
		close(fd[0]);
	}
}

void	create_pipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("Erreur lors de la création du pipe");
		exit(EXIT_FAILURE);
	}
}

static int	init_pipes(t_cmd *c)
{
	while (c)
	{
		create_pipe(c->pipes_fd);
		c = c->next;
	}
	return (1);
}

void	redir_io(t_cmd *c)
{
	if (c->heredoc != 0)
		heredoc(c);
	else if (c->fd_in != -1)
	{
		c->input_backup = dup(STDIN_FILENO);
		dup2(c->fd_in, STDIN_FILENO);
		close(c->fd_in);
	}
	if (c->fd_out != -1)
	{
		c->output_backup = dup(STDOUT_FILENO);
		dup2(c->fd_out, STDOUT_FILENO);
		close(c->fd_out);
	}
}

int	set_pipes(t_cmd *c)
{
	if (c->prev && c->prev->idx_cmd >= 0)
		dup2(c->prev->pipes_fd[0], STDIN_FILENO);
	if (c->next)
		dup2(c->pipes_fd[1], STDOUT_FILENO);
	return (1);
}


//in order we need to set pip[es, redirect close fds of the redirections
static void	child(t_cmd *c, t_shell *g_shell)
{
	close_cmds_fds(c);
	if (dispatcher_builtin(g_shell, c) == 0)
		exec_cmd(c->cmd, c, g_shell);
	exit_builtin(g_shell, 0);
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
		//close(cmds->output_backup);
		cmds->output_backup = -1;
	}
	if (cmds->input_backup != -1)
	{
		dup2(cmds->input_backup, STDIN_FILENO);
		//close(cmds->input_backup);
		cmds->output_backup = -1;
	}
}

void	close_cmds_fds(t_cmd *c)
{
	t_cmd	*tmp;

	tmp = c;
	while (tmp)
	{
		if (tmp->fd_in != -1)
			close(tmp->fd_in);
		if(tmp->fd_out != -1)
			close(tmp->fd_out);
		close_pipes_fds(c, NULL);
		tmp = tmp->next;
	}
}


//For each command determine the input and output
int	prepare_pipes_for_exec(t_shell *g_shell)
{
	t_cmd	*cmds;

	cmds = g_shell->cmds;
	if (g_shell->nb_cmds > 1)
		init_pipes(cmds);
	g_shell->pids = ft_calloc(g_shell->nb_cmds, sizeof(pid_t));
	if (g_shell->pids == NULL)
		return (0);
	return (1);
}

int	handle_pipes_cmd(t_shell *g_shell)
{
	t_cmd	*cmds;
	int		i;
	int		ret;

	i = 0;
	cmds = g_shell->cmds;
	ret = 0;
	while (i < g_shell->nb_cmds)
	{
		redir_io(cmds);
		ret = dispatcher_builtin(g_shell, cmds);
		restore_io(cmds);
		if (ret == 0)
		{
			g_shell->pids[i] = fork();
			if (g_shell->pids[i] < 0)
				return (0);
			if (g_shell->pids[i] == 0)
				child(cmds, g_shell);
		}
		i++;
		cmds = cmds->next;
	}
	close_pipes_fds(g_shell->cmds, NULL);
	close_cmds_fds(g_shell->cmds);
	i = -1;
	while (++i < g_shell->nb_cmds )
		waitpid(g_shell->pids[i], &g_last_exit_code, 0);
	free_pipes(g_shell);
	return (1);
}

int	handle_cmd(t_shell *g_shell)
{
	t_cmd	*c;
	int		ret;
	int		pid;

	c = g_shell->cmds;
	redir_io(c);
	ret = dispatcher_builtin(g_shell, c);
	restore_io(c);
	if (ret == 0)
	{
		pid = fork();
		if (pid < 0)
			return (0);
		if (pid == 0)
			child(c, g_shell);
	waitpid(pid, &g_last_exit_code, 0);
	}
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
