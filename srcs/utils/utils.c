/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:38:17 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/06 13:51:50 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_cmds(t_cmd *cmds)
{
	if (cmds != NULL)
	{
		if (cmds->full_cmd_path != cmds->cmd[0])
			cmds->full_cmd_path = ft_free_ptr(cmds->full_cmd_path);
		ft_free_split(cmds->cmd);
		cmds = ft_free_ptr(cmds);
	}
	cmds = NULL;
}

static void	*free_lst_cmd(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		del_cmds(cmds);
		cmds = tmp;
	}
	return (NULL);
}

void	*free_lst_token(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		if (tokens != NULL)
		{
			ft_free_ptr(tokens->value);
			tokens->value = NULL;
			ft_free_ptr(tokens);
		}
		tokens = tmp;
	}
	return (NULL);
}

static void	free_all(t_shell *g_shell)
{
	if (g_shell->list_token != NULL)
	{
		g_shell->list_token = free_lst_token(g_shell->list_token);
		g_shell->start_token->next = NULL;
	}
	if (g_shell->cmds != NULL)
	{
		g_shell->cmds = free_lst_cmd(g_shell->cmds);
		g_shell->start_cmd->next = NULL;
	}
	if (g_shell->pids != NULL)
		g_shell->pids = ft_free_ptr(g_shell->pids);
	if (g_shell->io != NULL)
		g_shell->io = ft_free_ptr(g_shell->io);
	close(g_shell->output_backup);
	close(g_shell->input_backup);
}

void	ft_free_shell(t_shell *g_shell, int last_exit)
{
	free_all(g_shell);
	if (last_exit)
	{
		ft_free_split(g_shell->split_env);
		g_shell->split_env = NULL;
		free_lst_token(g_shell->start_token->next);
	}
}
