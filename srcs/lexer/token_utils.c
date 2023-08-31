/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:33:43 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/31 12:11:26 by hdamitzi         ###   ########.fr       */
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

	new = ft_calloc(1, sizeof(t_token));
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



t_token *concat_literals(t_token *start, t_token *current, char *tmp)
{
	t_token	*new;
	t_token	*buff;
	char	*concat_value;

	current = start;
	concat_value = NULL;
	buff = NULL;
	while (current && current->type == literal)
	{
		if (buff)
			delone(buff);
		if (!concat_value)
			concat_value = ft_strdup(current->value);
		else
		{
			concat_value = ft_strjoin(concat_value, current->value);
			buff = current;
			free(tmp);
		}
		tmp = concat_value;
		current = current->next;
	}
	if (concat_value)
	{
		new = new_token(concat_value, literal, start->pos);
		new->next = current;
		return (free(concat_value), delone(start), new);
	}
	return (start);
}

void	last_quote_passage(t_token *lst)
{
	t_token	*prev;
	t_token	*current;
	char	*tmp;

	current = NULL;
	tmp = NULL;
	while (lst)
	{
		if (lst && lst->type == literal)
		{
			prev = lst->prev;
			lst = concat_literals(lst, current, tmp);
			lst->prev = prev;
			prev->next = lst;
		}
		lst = lst->next;
	}
}

void	quotes_neutralizer(t_shell *g_shell)
{
	t_token	*prev;
	t_token	*lst;

	lst = g_shell->list_token;
	while (lst)
	{
		if (lst && (lst->type == single_quote || \
		lst->type == double_quote))
		{
			prev = lst->prev;
			if (prev)
			{
				lst = concat_token(lst);
				prev->next = lst;
				lst->prev = prev;
			}
		}
		lst = lst->next;
	}
	lst = g_shell->start_token->next;
	last_quote_passage(lst);
	g_shell->list_token = g_shell->start_token->next;
}
