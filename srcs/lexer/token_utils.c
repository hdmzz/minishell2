/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:33:43 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/07/11 14:03:26 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	replace_token(t_token *start, t_token *end, t_token *new)
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
	else
	{
		start = new;
		start->next = NULL;
		start->prev = NULL;
	}
}

void	quotes_neutralizer(t_token **lst)
{
	t_token	*prev;
	t_token	*start;

	start = *lst;
	while ((*lst))
	{
		if ((*lst) && ((*lst)->type == single_quote || \
		(*lst)->type == double_quote))
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
