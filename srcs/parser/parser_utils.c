#include "../../include/minishell.h"

void	add_cmd_back(t_shell *g_shell, t_cmd *to_add)
{
	t_cmd	*temp;

	temp = g_shell->start_cmd;
	if (temp->next != NULL)
	{
		while (temp->next != NULL)
			temp = temp->next;
	}
	to_add->prev = temp;
	temp->next = to_add;
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

//need to add 1 to the result for the NULL one
int	count_split_size(t_token *token)
{
	t_token	*lst;
	int		split_size;

	lst = token;
	split_size = 0;
	if (lst && lst->type == pipeline)
		lst = lst->next;
	while (lst && lst->type != pipeline)//tant que l'on est pas sur un pipe
	{
		if (!(lst->type & 33))//si le token N'EST PAS un pipeline ou un whitespace
			split_size++;
		lst = lst->next;
	}
	return (split_size);
}

t_cmd	*create_new_cmd(t_token *token)
{
	t_cmd	*new;
	int		split_size;
	int		i;

	i = -1;
	split_size = count_split_size(token) + 1;///+1 pour le null a la fin
	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = ft_calloc(split_size, sizeof(char *));//leaks ici
	if (!new->cmd)
		return (NULL);
	if (token && token->type == pipeline)
		token = token->next;
	while (token && token->type != pipeline)
	{
		if (token->type != white_space)
			new->cmd[++i] = ft_strdup(token->value);
		token = token->next;
	}
	new->fd_in = -1;
	new->fd_out = -1;
	new->input_backup = -1;
	new->output_backup = -1;
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
	t_token	*lst;

	lst = g_shell->list_token;
	nb_pipes = count_pipes(g_shell->list_token);
	g_shell->nb_pipes = nb_pipes;
	g_shell->nb_cmds = nb_pipes + 1;
	nb_cmds = nb_pipes + 1;
	while (nb_cmds--)
	{
		add_cmd_back(g_shell, create_new_cmd(lst));
		if (lst->type == pipeline)
			lst = lst->next;
		while (lst && lst->type != pipeline)
			lst = lst->next;
	}
	g_shell->cmds = g_shell->start_cmd->next;
}
