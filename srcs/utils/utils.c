/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:38:17 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/19 19:35:35 by hdamitzi         ###   ########.fr       */
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
	if (cmds != NULL)
	{
		ft_free_split(cmds->cmd);
		ft_free_ptr(cmds);
	}
	cmds = NULL;
}

void	free_lst_cmd(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		del_cmds(cmds);
		cmds = tmp;
	}
	
}

void	free_lst_token(t_token *tokens)
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
}

static void	free_all(t_shell *g_shell, int last_exit)
{
	if (g_shell->list_token != NULL)
	{
		free_lst_token(g_shell->list_token);
		g_shell->list_token = NULL;
		g_shell->start_token->next = NULL;
	}
	if (g_shell->cmds != NULL)
	{
		free_lst_cmd(g_shell->cmds);
		g_shell->cmds = NULL;
		g_shell->start_cmd->next = NULL;
	}
	if (last_exit)
		ft_free_split(g_shell->split_env);
}

void	ft_free_shell(t_shell *g_shell, int last_exit)
{
	free_all(g_shell, last_exit);
}
