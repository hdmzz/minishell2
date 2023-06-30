/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:33:43 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/30 13:19:19 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*last_token(t_token *token)
{
	while (token->next != NULL)
		token = token->next;
	return (token);
}

t_token	*new_token(char *value, int type, int pos)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->type = type;
	new->pos = pos;
	new->next = NULL;
	return (new);
}

void	token_add_back(t_token **lst, t_token *to_add)
{
	t_token	*start;

	start = *lst;
	if (start == NULL)
	{
		*lst = to_add;
		(*lst)->prev = NULL;
		return ;
	}
	if (lst && *lst && to_add)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = to_add;
		to_add->prev = start;
	}
}

void	delone(t_token *to_del)
{
	if (to_del)
	{
		free(to_del->value);
		free(to_del);
	}
}

void	delfew(t_token *start, t_token *end)
{
	t_token	*temp;

	temp = start->next;
	while (temp != end)
	{
		delone(start);
		start = temp;
		temp = temp->next;
	}
	delone(start);
	delone(temp);
}

void	replace_token(t_token *start, t_token *end, t_token *new)
{
	t_token	*add_back;

	add_back = start->prev;
	delfew(start, end);
	if (add_back)
		add_back->next = new;
	else
	{
		start = new;
		start->next = NULL;
		start->prev = NULL;
	}
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
	return (new);
}

void	quotes_neutralizer(t_token **lst)
{
	t_token	*prev;
	t_token	*start;

	start = *lst;
	while ((*lst))
	{
		if ((*lst) && ((*lst)->type == single_quote || (*lst)->type == double_quote))
		{
			prev = (*lst)->prev;
			if (prev)
			{
				(*lst) = concat_token(*lst);
				prev->next = (*lst);
			}
			else
				start = concat_token(*lst);
		}
		(*lst) = (*lst)->next;
	}
	(*lst) = start;
}

//type = to_replace->type;
//	tmp = to_replace->next;
//	value = ft_strdup("");
//	buff = tmp->next;
//	while (tmp && buff && buff->type != type)
//	{
//		value = ft_strjoin(value, tmp->value);
//		delone(tmp);
//		tmp = buff;
//		buff = tmp->next;
//	}
//	value = ft_strjoin(value, tmp->value);
//	delone(tmp);
//	if (buff && buff->next)
//		buff = tmp->next;
//	else
//		buff = NULL;
//	free(to_replace->value);
//	to_replace->value = value;
//	to_replace->type = literal;
//	to_replace->next = buff;
