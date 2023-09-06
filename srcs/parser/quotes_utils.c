/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:53:19 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/06 14:33:10 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*quotes_appared(t_token *first_quote)
{
	t_token	*current;
	t_token	*last_same_quote;
	int		quote_type;

	current = first_quote;
	quote_type = current->type;
	current = current->next;
	while (current && current->type != quote_type)
		current = current->next;
	if (!current)
		return (NULL);
	last_same_quote = current;
	current = first_quote->next;
	while (current != last_same_quote)
	{
		if ((current->type == single_quote && quote_type == double_quote)
			|| (current->type == double_quote && quote_type == single_quote))
			current->type = literal;
		current = current->next;
	}
	return (last_same_quote);
}

bool	quotes_rules(t_token *token)
{
	while (token)
	{
		while (token && !(token->type & 192))
			token = token->next;
		if (token && token->type & 192)
		{
			token = quotes_appared(token);
			if (token == NULL)
				return (false);
		}
		if (token)
			token = token->next;
	}
	return (true);
}

char	*ev_expander(t_token *l)
{
	char	*ev;

	ev = var_xpanser(l->next->value, l->g_shell);
	return (ev);
}
