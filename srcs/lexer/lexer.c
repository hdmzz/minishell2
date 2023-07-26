/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:07:12 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/07/26 11:39:50 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	this is where we calaculate the size of each token
	the idea is to use th strchr function for each chararcter of input,
	sarch an occucrence in the string composed of all the metacharcter, control
	operators, and words
*/
int	token_len(char *input)
{
	int	len;

	len = 0 ;
	if (ft_strchr("><\t\n |$\\\"\'", *input))
	{
		if (!ft_strncmp("<<", input, 2) || !ft_strncmp(">>", input, 2))
			len = 2;
		else
			len = 1;
	}
	else
	{
		while (!ft_strchr("><\t\n |$\\\"\'", input[len]))
			len ++;
	}
	return (len);
}

int	get_token_type(char *str)
{
	int	i;
	static t_token_trslte	tok_type[] = {
	{"\n", new_line, "new_line"},
	{" ", white_space, "white_space"},
	{"\t", white_space, "white_space"},
	{"|", pipeline, "pipeline"},
	{"\'", single_quote, "single_quote"},
	{"\"", double_quote, "double_quote"},
	{"<", simple_redir_left, "simple_redir_left"},
	{">", simple_redir_right, "simple_redir_right"},
	{"<<", double_redir_left, "double_redir_left"},
	{">>", double_redir_right, "double_redir_right"},
	{"$", dollar, "dollar"},
	{NULL, -1, NULL}
	};

	i = -1;
	while (tok_type[++i].type != -1)
		if (!ft_strcmp(tok_type[i].value, str))
			return (tok_type[i].type);
	return (0);
}

void	print_lst(t_token *token)
{
	while (token && token->next != NULL)
	{
		printf(":%s:%d:%d:\n", token->value,token->type, token->pos);
		token = token->next;
	}
	if (token)
		printf(":%s:%d:%d:\n", token->value,token->type, token->pos);
}

void print_cmd(char **cmds)
{
	int i = -1;
	while (cmds[++i])
		printf("%s\n", cmds[i]);
}

/*
	this function calculates the token size
	ten malloc the size of the token and add it to the list
	in arguments
*/
int	create_token(t_token **lst, char **input, int *pos)
{
	char	*value;
	int		token_size;
	int		type;
	t_token	*new;

	token_size = token_len(*input);//ici on a la longeur de ce que l'on va mettre ds la value
	if (token_size == 0)
		return (0);
	value = ft_strndup((*input), token_size);
	if (!value)
		return (0);
	type = get_token_type(value);
	if (!type)
		type = literal;
	new = new_token(value, type, *pos);
	if (!new)
		return (free(value), 0);
	token_add_back(lst, new);
	*input += token_size;
	*pos += 1;
	return (1);
}

/*
*	The function recovers the command then for each
*	create a token with the value and the token type
*/
t_token	*lexer(t_shell *g_shell)
{
	int		i;
	t_token	*token;
	char	*input;

	i = 1;
	token = new_token("", start_type, 0);
	input = g_shell->start_buff;
	if (!input)
		return (NULL);
	while (*input != 0)
	{
		if (!create_token(&token, &input, &i))
		{
			//free token list etc
			exit(EXIT_FAILURE);
		}
	}
	g_shell->start_token = token;
	return (token->next);
}
