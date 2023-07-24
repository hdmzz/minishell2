/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:11:10 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/07/24 11:33:11 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//This function is used to concat the words token at the end
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
		return (free(value), start);
	if (tmp && tmp->type == white_space)
		tmp = tmp->next;
		//pb ici on reconcate les redir avec les litteral 
		//on pourait
	while (tmp && !(tmp->type & 1))//tant que lon est pas sur un token de controle or il faut concat meme les redirections
	{
		buff = value;
		value = ft_strjoin(value, tmp->value);
		free(buff);
		last_to_del = tmp;
		tmp = tmp->next;
	}
	new = new_token(value, literal, start->pos);
	new->next = tmp;
	new->prev = start->prev;
	delfew(start, last_to_del);
	new->prev->next = new;
	return (new);
}

//on arrive a la fin il faut recncat
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
		free(buff);
		tmp = tmp->next;
	}
	new = new_token(value, literal, start->pos);
	new->next = tmp->next;
	new->prev = start->prev;
	delfew(start, tmp);
	new->prev->next = new;
	return (new);
}

void	delone(t_token *to_del)
{
	if (to_del)
	{
		if (to_del->prev)
			to_del->prev->next = to_del->next;
		if (to_del->next)
			to_del->next->prev = to_del->prev;
		free(to_del->value);
		free(to_del);
	}
}

void	delfew(t_token *start, t_token *end)
{
	t_token	*temp;

	temp = start->next;
	if (start == end)
		return (delone(start));
	while (temp && temp != end)
	{
		delone(start);
		start = temp;
		temp = temp->next;
	}
	delone(start);
	delone(temp);
}
