/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:11:10 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/05 00:31:07 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*final_concat(t_token *start)
{
	t_token	*tmp;
	t_token	*new;
	t_token	*last_to_del;
	char	*value;
	char	*buff;

	value = ft_strdup("");
	tmp = start;
	if (tmp == NULL)
		return (ft_free_ptr(value), start);
	if (tmp && tmp->type == white_space)
		tmp = tmp->next;
	while (tmp && !(tmp->type & 1))
	{
		buff = value;
		value = ft_strjoin(value, tmp->value);
		ft_free_ptr(buff);
		last_to_del = tmp;
		tmp = tmp->next;
	}
	new = new_token(value, literal, start->pos);
	new->next = tmp;
	new->prev = start->prev;
	new->prev->next = new;
	return (delfew(start, last_to_del), new);
}

int	concat_word(t_shell *g_shell)
{
	t_token	*temp;

	temp = g_shell->list_token;
	while (temp)
	{
		if (temp && (temp->type == literal || temp->type == white_space))
			temp = final_concat(temp);
		temp = temp->next;
	}
	g_shell->list_token = g_shell->start_token->next;
	return (1);
}

t_token	*concat_token(t_token *start)
{
	t_token	*tmp;
	t_token	*new;
	char	*value;
	char	*buff;
	int		type;

	value = ft_strdup("");
	type = start->type;
	tmp = start->next;
	while (tmp->type != type)
	{
		buff = value;
		value = ft_strjoin(value, tmp->value);
		buff = ft_free_ptr(buff);
		tmp = tmp->next;
	}
	new = new_token(value, literal, start->pos);
	new->next = tmp->next;
	new->hd_delim_into_quotes = start->hd_delim_into_quotes;
	delfew(start, tmp);
	value = ft_free_ptr(value);
	return (new);
}

void	*delone(t_token *to_del)
{
	if (to_del)
	{
		if (to_del->prev)
			to_del->prev->next = to_del->next;
		if (to_del->next)
			to_del->next->prev = to_del->prev;
		to_del->value = ft_free_ptr(to_del->value);
		to_del = ft_free_ptr(to_del);
	}
	return (NULL);
}

void	delfew(t_token *start, t_token *end)
{
	t_token	*temp;

	if (start == end)
		delone(start);
	else
	{
		temp = start->next;
		while (temp && temp != end)
		{
			delone(start);
			start = NULL;
			start = temp;
			temp = temp->next;
		}
		delone(start);
		delone(temp);
		temp = NULL;
		start = NULL;
	}
}
