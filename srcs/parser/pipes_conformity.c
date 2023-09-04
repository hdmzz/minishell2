/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_conformity.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:22:32 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/04 12:22:48 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	pipe_then_space(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp && temp->type != pipeline)
		temp = temp->next;
	if (temp && temp->type == pipeline)
		temp = temp->next;
	while (temp && temp->type == white_space)
		temp = temp->next;
	if (temp && temp->type != literal)
		return (true);
	return (false);
}

static bool	no_cmd_btw_pipes(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		if (temp->type == pipeline)
		{
			temp = temp->next;
			while (temp && temp->type == white_space)
				temp = temp->next;
			if (temp && temp->type == pipeline)
				return (true);
		}
		if (temp)
			temp = temp->next;
	}
	return (false);
}

static bool	space_then_pipe(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp && temp->type == white_space)
		temp = temp->next;
	if (temp && temp->type == pipeline)
		return (true);
	return (false);
}

bool	pipes_conformity(t_shell *g_shell)
{
	t_token	*token;

	token = g_shell->list_token;
	while (token && token->type == white_space)
		token = token->next;
	if (token && token->type == pipeline)
		return (false);
	if (no_cmd_btw_pipes(token))
		return (false);
	if (space_then_pipe(token))
		return (false);
	if (pipe_then_space(token))
		return (false);
	return (true);
}
