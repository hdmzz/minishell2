/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:07:12 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/19 19:37:54 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	this is where we calaculate the size of each token
	the idea is to use th strchr function for each chararcter of input,
	sarch an occucrence in the string composed of all the metacharcter, control
	operators, and words
	no need to do a simple ft_strcmp because the double quote can be glued to the next word
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
static t_token	*create_token(char **input, int *pos)
{
	char	*value;
	int		token_size;
	int		type;
	t_token	*new;

	token_size = token_len(*input);
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
		return (ft_free_ptr(value), NULL);
	ft_free_ptr(value);
	*input += token_size;
	*pos += 1;
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
		(*lst)->next = NULL;
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

/*
*	The function recovers the command then for each
*	create a token with the value and the token type
*/
int	lexer(t_shell *g_shell)
{
	int		i;
	t_token	*new_token;
	char	*input;

	i = 1;
	input = g_shell->start_buff;
	if (input == NULL)
		exit_builtin(g_shell);
	while (*input != 0)
	{
		new_token = create_token(&input, &i);
		if (new_token == NULL)
			return (0);
		token_add_back(&g_shell->start_token, new_token);
	}
	g_shell->list_token = g_shell->start_token->next;
	return (1);
}
