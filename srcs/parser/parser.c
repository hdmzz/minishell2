/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:47:34 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/30 12:37:30 by hdamitzi         ###   ########.fr       */
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

int	check_last_token(t_token *last)
{
	int	type;

	type = last->type;
	if (type != literal && type != white_space && type  != double_quote \
	&& type != single_quote && type != dollar && type != new_line)
		return (0);
	return (1);
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
		*tokens = (*tokens)->next;//tokens est mis a null a la fin de tous les tours
	}
	*tokens = start;
	if (!check_last_token(last_token(*tokens)))
		return (0);
	quotes_neutralizer(tokens);
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

//les tokens DOLLAR:
// On récupère le token DOLLAR + le token suivant qui doit être un token WORD.
// On cherche le contenu du token WORD dans l'environnement et on récupère la valeur de la variable concernée 
// ou NULL si la variable concernée n'existe pas. On remplace ces deux tokens par un token WORD avec le contenu
//  nouvellement récupéré. On fait la même chose lorsqu'on trouve un token DOLLAR entre double quotes,
//  puisqu'il n'y aucune interprétation à effectuer si le token DOLLAR est entre simple quote.
