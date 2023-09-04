/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:09:20 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/04 14:02:11 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prepare_pipes_for_exec(t_shell *g_shell)
{
	t_cmd	*cmds;

	cmds = g_shell->cmds;
	if (g_shell->nb_cmds > 1)
		init_pipes(cmds);
	return (1);
}

void	create_pipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("Erreur lors de la création du pipe");
		exit(EXIT_FAILURE);
	}
}

int	init_pipes(t_cmd *c)
{
	while (c)
	{
		create_pipe(c->pipes_fd);
		c = c->next;
	}
	return (1);
}

int	set_pipes(t_cmd *c, t_shell *g)
{
	if (c->prev && c->prev->idx_cmd >= 0)
		dup2(c->prev->pipes_fd[0], STDIN_FILENO);
	if (c->next)
		dup2(c->pipes_fd[1], STDOUT_FILENO);
	close_pipes_fds(g->cmds, NULL);
	return (1);
}

int	wait_children(t_shell *g_shell)
{
	int		i;
	int		status;
	pid_t	ret;

	i = -1;
	status = 0;
	ret = 0;
	close_cmds_fds(g_shell->cmds);
	while (++i < g_shell->nb_cmds)
	{
		ret = waitpid(g_shell->pids[i], &status, 0);
		if (ret == -1)
			break ;
	}
	if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	free_pipes(g_shell);
	return (status);
}
