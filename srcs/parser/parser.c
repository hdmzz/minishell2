/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:47:34 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/03 16:14:58 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_last_token(t_token *last)
{
	int	type;

	if (last == NULL)
		return (1);
	type = last->type;
	if (type != literal && type != white_space && type != double_quote \
	&& type != single_quote && type != dollar && type != new_line)
		return (0);
	return (1);
}

/*
*	grammatical analysis of all the tokens of the list
*	the first point to verify is i we hae quotes and if 
*/
int	grammatical_analyzer(t_token **tokens, t_shell *g_shell)
{
	t_token	*tmp;
	int		type;

	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == double_quote || tmp->type == single_quote)
		{
			type = tmp->type;
			if (!quotes_rules(tmp))
				return (0);
			tmp = tmp->next;
			while (tmp->type != type)
				tmp = tmp->next;
			tmp = tmp->next;
		}
		if (tmp)
			tmp = tmp->next;
	}
	tmp = *tokens;
	if (!check_last_token(last_token(tmp)))
		return (0);
	dollar_rule(g_shell, g_shell->start_token->next, 0);
	heredoc_first_analyzer(g_shell);
	return (quotes_neutralizer(g_shell), 1);
}

char	*var_xpanser(char *input)
{
	char	*ev;

	if (*input == '$')
		input++;
	if (*input == '?')
		return (ft_itoa(g_last_exit_code));
	else
		ev = getenv(input);
	return (ev);
}

void	dollar_rule(t_shell *g_shell, t_token *lst, int quote_count)
{
	bool	interpretation;
	char	*ev;

	interpretation = true;
	while (lst)
	{
		if (lst->type == single_quote && !(quote_count % 2))
		{
			quote_count += 1;
			interpretation = false;
		}
		if (lst->type == dollar && lst->next->type == literal && interpretation)
		{
			ev = var_xpanser(lst->next->value);
			if (ev != NULL)
				lst = replace_token(lst, lst->next, new_token(ev, literal, lst->pos));
			else
				lst = replace_token(lst, lst->next, new_token("", literal, lst->pos));
		}
		lst = lst->next;
	}
	g_shell->list_token = g_shell->start_token->next;
}

int	parser(t_shell *g_shell)
{
	int	ret;

	ret = 0;
	if (ft_strlen(g_shell->start_buff) == 0)
		return (EXIT_SUCCESS);
	add_history(g_shell->start_buff);
	if (!grammatical_analyzer(&g_shell->list_token, g_shell))
		return (error_parsing_handler("syntax error", NULL, 2, 0));
	if (!pipes_conformity(g_shell))
		return (error_parsing_handler("pipe error", NULL, 2, 0));
	if (!check_redirection_rules(g_shell))
		return (error_parsing_handler("redirection error", NULL, 2, 0));
	compose_cmd(g_shell);
	return (ret);
}
