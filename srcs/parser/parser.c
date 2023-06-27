/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:47:34 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/25 00:14:44 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//wile we are in between two same type quotes we neutralize the other quotes met
//but if there is no matching quotes there is a syntax problem
bool	check_quote(t_token **token)
{
	int		type;
	bool	found_matching_quote;

	type = (*token)->type;
	*token = (*token)->next;
	found_matching_quote = false;
	while (*token && (*token)->type != type)
	{
		if (type == double_quote && (*token)->type == single_quote)
			(*token)->type = literal;
		if (type == single_quote && (*token)->type == double_quote)
			(*token)->type = literal;
		*token = (*token)->next;
	}
	if (*token && (*token)->type == type)
		found_matching_quote = true;
	return (found_matching_quote);
}

//quotes works by two if one is open there must be another quote of the same
//type to close th opening if we count the number of quotes and the modulo
//by 2 of this number is not 0 the we have a syntax problem or imbricated quotes
//of different types the the inbetween quotes must be neutralized
bool	quotes_rules(t_token **token)
{
	if (!check_quote(token))
	{
		error_handler("Syntax error");
		print_lst(*token);
		return (false);
	}
	return (true);
}

/*
*	grammatical analysis of all the tokens of the list
*	the first point to verify is i we hae quotes and if 
*/
int	grammatical_analyzer(t_token **tokens)
{
	t_token	*start;

	start = *tokens;
	while (*tokens)
	{
		if ((*tokens)->type == double_quote || (*tokens)->type == single_quote)
		{
			if (!quotes_rules(tokens))
				return (0);
		}
		*tokens = (*tokens)->next;
	}
	*tokens = start;
	print_lst(*tokens);
	return (1);
}

/*
*	stock the command splitted in an array
*	then search the binary file in the PATH
*/
int	parser(t_shell *g_shell)
{
	lexer(g_shell);
	grammatical_analyzer(&g_shell->list_token);
	//exec(g_shell);
	//ft_free_split(g_shell->splitted_cmd);
	return (1);
}
