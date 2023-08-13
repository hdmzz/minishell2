/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:38:17 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/13 14:18:33 by hdamitzi         ###   ########.fr       */
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
	if (cmds->cmd != NULL)
		ft_free_split(cmds->cmd);
	if (cmds != NULL)
		free(cmds);
	cmds = NULL;
}

//q: comment free une liste chainee de t_cmd?
//r: on parcourt la liste chainee et on free chaque element
//q: comment free une liste chainee de t_token?

//r: on parcourt la liste chainee et on free chaque element
//il faut une fonction qui parcour la liste chainee et qui free chaque element
//il faut une fonction qui free les tokens
//il faut une fonction qui free les cmds

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
	t_token	*tmp2;
	
	tmp2 = tokens;
	while (tokens)
	{
		tmp = tokens->next;
		if (tokens != NULL)
		{
			free(tokens->value);
			free(tokens);
		}
		tokens = tmp;
	}
	tmp2 = NULL;
}

static void	free_all(t_shell *g_shell, int last_exit)
{
	if (g_shell->list_token != NULL)
	{
		free_lst_token(g_shell->list_token);
		g_shell->list_token = NULL;
		g_shell->start_token->next = NULL;
	}
}

void	ft_free_shell(t_shell *g_shell, int last_exit)
{
	free_all(g_shell, last_exit);
}
