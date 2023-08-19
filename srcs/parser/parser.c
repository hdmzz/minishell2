/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:47:34 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/19 19:43:25 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//wile we are in between two same type quotes we neutralize the other quotes met
//but if there is no matching quotes there is a syntax problem
static bool	check_quote(t_token *token)
{
	int		type;
	bool	found_matching_quote;
	t_token	*tmp;

	tmp = token;
	type = tmp->type;
	tmp = token->next;
	found_matching_quote = false;
	while (tmp && tmp->type != type)
	{
		if (type == double_quote && tmp->type == single_quote)
			tmp->type = literal;
		if (type == single_quote && tmp->type == double_quote)
			tmp->type = literal;
		tmp = tmp->next;
	}
	if (tmp && tmp->type == type)
		found_matching_quote = true;
	return (found_matching_quote);
}

//quotes works by two if one is open there must be another quote of the same
//type to close th opening if we count the number of quotes and the modulo
//by 2 of this number is not 0 the we have a syntax problem or imbricated quotes
//of different types the the inbetween quotes must be neutralized
bool	quotes_rules(t_token *token)
{
	if (!check_quote(token))
	{
		error_handler("Syntax error");
		return (false);
	}
	return (true);
}

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

	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == double_quote || tmp->type == single_quote)
		{
			if (!quotes_rules(tmp))
				return (0);
		}
		tmp = tmp->next;
	}
	tmp = *tokens;
	if (!check_last_token(last_token(tmp)))
		return (0);
	dollar_rule(g_shell);
	heredoc_first_analyzer(g_shell);
	quotes_neutralizer(g_shell);
	return (1);
}

char	*var_xpanser(char *input)
{
	char	*ev;

	if (*input == '$')
		input++;
	ev  = getenv(input);
	return (ev);
}

void	dollar_rule(t_shell *g_shell)
{
	t_token	*lst;
	bool	interpretation;
	int		quote_count;
	char	*ev;

	lst = g_shell->start_token->next;
	interpretation = true;
	quote_count = 0;
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
			{
				lst = replace_token(lst, lst->next, new_token(ev, literal, lst->pos));
			}
			else
				lst = replace_token(lst, lst->next, new_token("", literal, lst->pos));
		}
		lst = lst->next;
	}
	g_shell->list_token = g_shell->start_token->next;
}

/*
*	stock the command splitted in an array
*	then search the binary file in the PATH
*/
int	parser(t_shell *g_shell)
{
	if (g_shell->start_buff == NULL)
		exit_builtin(g_shell);
	if (ft_strlen(g_shell->start_buff) == 0)
		return (1);
	add_history(g_shell->start_buff);
	if (!grammatical_analyzer(&g_shell->list_token, g_shell))
		return (0);
	if (!pipes_conformity(g_shell))
		return (0);
	if (!check_redirection_rules(g_shell))
		return (0);
	compose_cmd(g_shell);
	cmd_handler(g_shell);
	if (recover_fd(g_shell) == 0)
		return (0);
	return (1);
}
