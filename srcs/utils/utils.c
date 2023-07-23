/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:38:17 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/07/23 16:35:48 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	del_cmds(t_cmd *cmds)
{
	ft_free_split(cmds->cmd);
	free(cmds);
}

static void	free_all(t_shell *g_shell)
{
	t_cmd	*tmp_cmds;

	tmp_cmds = g_shell->cmds;
	delfew(g_shell->start_token, last_token(g_shell->start_token));
	while (g_shell->cmds)
	{
		tmp_cmds = g_shell->cmds->next;
		del_cmds(g_shell->cmds);
		g_shell->cmds = tmp_cmds;
	}
}

void	ft_free_shell(t_shell *g_shell)
{
	if (g_shell->full_cmd_path != NULL)
		free(g_shell->full_cmd_path);
	if (g_shell->splitted_cmd != NULL)
		ft_free_split(g_shell->splitted_cmd);
	if (g_shell->start_buff != NULL)
		free(g_shell->start_buff);
	free_all(g_shell);
}
