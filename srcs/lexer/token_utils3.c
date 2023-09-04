/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:19:52 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/05 00:37:46 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cln_whitespace_btw_ctrl_tok(t_shell *g_shell)
{
	t_token	*temp;

	temp = g_shell->list_token;
	while (temp)
	{
		if (temp->next && (temp->type & 31))
		{
			while (temp->next && temp->next->type == white_space)
				delone(temp->next);
		}
		if (temp->prev && (temp->type & 31))
		{
			while (temp->prev && temp->prev->type == white_space)
				delone(temp->prev);
		}
		temp = temp->next;
	}
}

int	check_redirection_rules(t_shell *g_shell)
{
	t_token	*temp;

	temp = g_shell->list_token;
	while (temp)
	{
		if (temp->type & 31)
		{
			temp = temp->next;
			while (temp && temp->type == white_space)
				temp = temp->next;
			if (!temp || (temp && temp->type != literal))
				return (0);
		}
		if (temp)
			temp = temp->next;
	}
	return (1);
}

t_token	*conc_lit(t_token *next, char *value, int pos)
{
	t_token	*new;

	new = new_token(value, literal, pos);
	new->next = next;
	value = ft_free_ptr(value);
	return (new);
}

t_token	*concat_literals(t_token *start, t_token *cur, t_token *buff, char *tmp)
{
	char	*concat_value;
	t_token	*new;

	cur = start;
	concat_value = NULL;
	while (cur && cur->type == literal)
	{
		if (buff)
			buff = delone(buff);
		if (!concat_value)
			concat_value = ft_strdup(cur->value);
		else
		{
			concat_value = ft_strjoin(concat_value, cur->value);
			free(tmp);
		}
		buff = cur;
		tmp = concat_value;
		cur = cur->next;
	}
	if (concat_value)
	{
		new = conc_lit(cur, concat_value, 1);
		return (buff = delone(buff), new);
	}
	return (start);
}

void	clean_trash(t_token *trash)
{
	t_token	*tmp;

	tmp = trash;
	while (tmp && tmp->type == literal)
	{
		trash = trash->next;
		tmp = ft_free_ptr(tmp);
		tmp = trash;
	}
}
