/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:23:13 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/06 00:09:40 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_cmd_tab(char **cmd, int first_redir, int end)
{
	while (first_redir && first_redir != end)
	{
		ft_free_ptr(cmd[first_redir]);
		cmd[first_redir] = NULL;
		first_redir++;
	}
}

void	recover_or_io(t_cmd *cmd)
{
	if (cmd->fd_out != -1)
		dup2(cmd->output_backup, STDOUT_FILENO);
	if (cmd->fd_in != -1)
		dup2(cmd->input_backup, STDIN_FILENO);
}

int	recover_fd(t_shell *g_shell)
{
	int	ret;

	ret = 1;
	if (g_shell->output_backup != -1 && g_shell->output_backup != STDOUT_FILENO)
	{
		if (dup2(g_shell->output_backup, STDOUT_FILENO) == -1)
			ret = 0;
	}
	if (g_shell->input_backup != -1 && g_shell->input_backup != STDIN_FILENO)
	{
		if (dup2(g_shell->input_backup, STDIN_FILENO) == -1)
			ret = 0;
	}
	return (ret);
}

void	redir_io(t_cmd *c)
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
