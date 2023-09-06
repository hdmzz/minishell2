/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:15:34 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/06 17:55:33 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(t_cmd *c, t_shell *g_shell)
{
	int	ret;

	if (g_shell->nb_cmds > 1)
		set_pipes(c, g_shell);
	redir_io(c);
	ret = dispatcher_builtin(g_shell, c);
	if (c->fd_in != -1)
		close(c->fd_in);
	if (c->fd_out != -1)
		close(c->fd_out);
	if (ret == COMMAND_NOT_FOUND)
		ret = exec_cmd(c->cmd, c, g_shell);
	exit_builtin(g_shell, ret);
}

int	create_children(t_cmd *c, t_shell *g_shell)
{
	int	i;

	i = 0;
	while (i < g_shell->nb_cmds)
	{
		g_shell->pids[i] = fork();
		if (g_shell->pids[i] < 0)
			return (error_handler(c->cmd[0], NULL, \
			strerror(errno), EXIT_FAILURE));
		if (g_shell->pids[i] == 0)
			child(c, g_shell);
		i++;
		c = c->next;
	}
	return (wait_children(g_shell));
}

static int	handle_pipes_cmd(t_shell *g_shell)
{
	t_cmd	*cmds;

	cmds = g_shell->cmds;
	return (create_children(cmds, g_shell));
}

static int	handle_cmd(t_shell *g_shell)
{
	t_cmd	*c;
	int		ret;

	c = g_shell->cmds;
	redir_io(c);
	ret = dispatcher_builtin(g_shell, c);
	restore_io(c);
	if (ret == 127)
		return (create_children(c, g_shell));
	return (ret);
}

int	cmd_handler(t_shell *g_shell)
{
	if (g_shell->start_buff != NULL)
	{
		if (ft_strlen(g_shell->start_buff) == 0)
			return (EXIT_SUCCESS);
	}
	g_shell->start_buff = ft_free_ptr(g_shell->start_buff);
	g_shell->pids = ft_calloc(g_shell->nb_cmds, sizeof(pid_t));
	if (g_shell->pids == NULL)
		return (EXIT_FAILURE);
	if (g_shell->nb_cmds == 1)
		return (handle_cmd(g_shell));
	else
	{
		prepare_pipes_for_exec(g_shell);
		return (handle_pipes_cmd(g_shell));
	}
	return (1);
}
