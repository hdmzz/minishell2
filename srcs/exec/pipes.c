/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 01:54:22 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/28 02:17:29 by hdamitzi         ###   ########.fr       */
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

void	redir_io(t_cmd *c)//il ne faut pas tout fermer de suite le in et le out  car en cas de commande seule on en a besoin apres
{
	if (c->heredoc != 0)
		heredoc(c);
	else if (c->fd_in != -1)
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
	while (i < g_shell->nb_cmds)
	{
		set_pipes(cmds);
		redir_io(cmds);
		ret = dispatcher_builtin(g_shell, cmds);
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
	//process oparents doit fermer tout les fd apres execution de toutes les cmds
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
