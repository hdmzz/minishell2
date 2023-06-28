/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:33:43 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/28 14:40:43 by hdamitzi         ###   ########.fr       */
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

void	delone(t_token *to_del)
{
	if (to_del)
	{
		free(to_del->value);
		free(to_del);
	}
}

void	concat_token(t_token *to_replace)
{
	t_token	*tmp;
	//t_token	*replace_by;
	char	*value;
	int		type;

	type = to_replace->type;
	tmp = to_replace->next;
	while (tmp && tmp->type != type)//si on arrive sur le mem type de token on sarrete on peut donc recuperer la suite qui nous interresse
	{
		if (!value)
			value = ft_strjoin("", tmp->value);
		else
			value = ft_strjoin(value, tmp->value);
		tmp = tmp->next;
	}//ici on a accumule toute les valeures contenue dans les tokens  entre quotes
	if (tmp && tmp->next)
		tmp = tmp->next;
	printf("tmp next %s\n", tmp->value);
}

void	quotes_neutralizer(t_token *lst)
{
	while (lst)
	{
		if (lst->type == single_quote || lst->type == double_quote)
			concat_token(lst);
		lst = lst->next;
	}
}
