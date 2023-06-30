/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:33:43 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/30 11:33:17 by hdamitzi         ###   ########.fr       */
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
		return ;
	}
	if (lst && *lst && to_add)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = to_add;
	}
}

void	token_add_middle(t_token **lst, t_token *to_add)
{
	if ((*lst)->value == NULL)
		(*lst) = to_add;
	else
		(*lst)->next = to_add;
}

void	delone(t_token *to_del)
{
	if (to_del)
	{
		free(to_del->value);
		free(to_del);
	}
}

void	delfew(t_token *start, int type)
{
	t_token	*temp;

	start = start->next;
	temp = start;
	while (start->type != type)
	{
		delone(temp);
		temp = NULL;
		temp = start;
		start = start->next;
	}
	delone(temp);
	delone(start);
	
}

void	concat_token(t_token *to_replace)
{
	t_token	*tmp;
	t_token	*buff;
	char	*value;
	int		type;

	type = to_replace->type;
	tmp = to_replace->next;
	value = ft_strdup("");
	buff = tmp->next;
	while (tmp && buff && buff->type != type)
	{
		value = ft_strjoin(value, tmp->value);
		delone(tmp);
		tmp = buff;
		buff = tmp->next;
	}
	value = ft_strjoin(value, tmp->value);
	delone(tmp);
	if (buff && buff->next)
		buff = tmp->next;
	else
		buff = NULL;
	free(to_replace->value);
	to_replace->value = value;
	to_replace->type = literal;
	to_replace->next = buff;
}

void	quotes_neutralizer(t_token *lst)
{
	while (lst)
	{
		if (lst && (lst->type == single_quote || lst->type == double_quote))
			concat_token(lst);
		lst = lst->next;
	}
}
