/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 01:50:00 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/28 02:01:07 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes_fds(t_cmd *cmds, t_cmd *cur)
{
	while (cmds)
	{
		if (cmds && cmds != cur)
			close_fds(cmds->pipes_fd);
		cmds = cmds->next;
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

void	free_pipes(t_shell *g_shell)
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
