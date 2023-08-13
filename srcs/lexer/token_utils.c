/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:33:43 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/13 14:21:59 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*last_token(t_token *token)
{
	while (token && token->next != NULL)
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
	new->prev = NULL;
	return (new);
}

t_token	*replace_token(t_token *start, t_token *end, t_token *new)
{
	t_token	*add_back;
	t_token	*last_to_save;

	add_back = start->prev;
	last_to_save = end->next;
	delfew(start, end);
	if (add_back)
	{
		add_back->next = new;
		new->next = last_to_save;
		new->prev = add_back;
		if (last_to_save)
			last_to_save->prev = new;
	}
	return (new);
}

void	quotes_neutralizer(t_token **lst)
{
	t_token	*prev;
	t_token	*start;
	t_token	*temp;

	start = *lst;
	while ((*lst))
	{
		if ((*lst) && ((*lst)->type == single_quote || \
		(*lst)->type == double_quote))
		{
			prev = (*lst)->prev;
			if (prev)
			{
				temp = concat_token(*lst);//ICI tout les token entre quotes se sont fait del
				prev->next = temp;
				temp->prev = prev;
			}
			else
			{
				start = concat_token(*lst);
				start->prev = NULL;
				(*lst) = start;
			}
		}
		(*lst) = (*lst)->next;
	}
	(*lst) = start;
}
