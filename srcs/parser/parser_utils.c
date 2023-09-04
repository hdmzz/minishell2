/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:18:04 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/04 15:21:27 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cmd_back(t_shell *g_shell, t_cmd *to_add)
{
	t_cmd	*temp;

	temp = g_shell->start_cmd;
	to_add->full_cmd_path = get_cmd_path(to_add->cmd, g_shell);
	to_add->g_shell = g_shell;
	if (temp->next != NULL)
	{
		while (temp->next != NULL)
			temp = temp->next;
	}
	to_add->prev = temp;
	temp->next = to_add;
	ft_memset(to_add->pipes_fd, -1, sizeof(int) * 2);
}

int	count_pipes(t_token *lst)
{
	t_token	*tmp;
	int		pipes_count;

	tmp = lst;
	pipes_count = 0;
	while (tmp)
	{
		if (tmp->type == pipeline)
			pipes_count += 1;
		tmp = tmp->next;
	}
	return (pipes_count);
}

int	count_split_size(t_token *token)
{
	t_token	*lst;
	int		split_size;

	lst = token;
	split_size = 0;
	if (lst && lst->type == pipeline)
		lst = lst->next;
	while (lst && lst->type != pipeline)
	{
		if (!(lst->type & 33))
			split_size++;
		lst = lst->next;
	}
	return (split_size);
}

t_cmd	*create_new_cmd(t_token *token, int i, int split_size, int idx)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = ft_calloc(split_size, sizeof(char *));
	if (!new->cmd)
		return (NULL);
	if (token && token->type == pipeline)
		token = token->next;
	while (token && token->type != pipeline)
	{
		if (token->type != white_space)
			new->cmd[++i] = ft_strdup(token->value);
		if (token->hd_delim_into_quotes)
			new->hd_delim_into_quotes = token->hd_delim_into_quotes;
		token = token->next;
	}
	new->fd_in = -1;
	new->fd_out = -1;
	new->input_backup = -1;
	new->output_backup = -1;
	new->idx_cmd = idx;
	return (new);
}

/* 
	here we are gonna take the list token and create a command node
	based directly on the token no need to split and concat
 */
void	compose_cmd(t_shell *g_shell)
{
	int		nb_pipes;
	int		nb_cmds;
	int		idx;
	t_token	*lst;

	lst = g_shell->list_token;
	nb_pipes = count_pipes(g_shell->list_token);
	g_shell->nb_pipes = nb_pipes;
	g_shell->nb_cmds = nb_pipes + 1;
	nb_cmds = nb_pipes + 1;
	idx = 0;
	while (nb_cmds--)
	{
		add_cmd_back(g_shell, create_new_cmd(lst, -1, \
		count_split_size(lst) + 1, idx));
		if (lst->type == pipeline)
			lst = lst->next;
		while (lst && lst->type != pipeline)
			lst = lst->next;
		idx++;
	}
	g_shell->cmds = g_shell->start_cmd->next;
	prepare_io(g_shell->cmds);
}
