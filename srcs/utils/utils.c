/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:38:17 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/07/23 17:46:28 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 
	needed to count the numbers of elemnet in a command to 
	get rid of th arrows and the nme of the file after 
	in order to give  the execve function just thcommand
 */
int	split_lenght(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

void	del_cmds(t_cmd *cmds)
{
	ft_free_split(cmds->cmd);
	free(cmds);
	cmds = NULL;
}

static void	free_all(t_shell *g_shell)
{
	t_cmd	*tmp_cmds;

	tmp_cmds = g_shell->cmds;
	delfew(g_shell->start_token, last_token(g_shell->start_token));
	g_shell->start_token = NULL;
	g_shell->list_token = NULL;
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
	{
		free(g_shell->full_cmd_path);
		g_shell->full_cmd_path = NULL;
	}
	if (g_shell->splitted_cmd != NULL)//on s'en sert meme plus de ca
	{
		ft_free_split(g_shell->splitted_cmd);
		g_shell->splitted_cmd = NULL;
	}
	if (g_shell->start_buff != NULL)
	{
		free(g_shell->start_buff);
		g_shell->start_buff = NULL;
	}
	free_all(g_shell);
}
