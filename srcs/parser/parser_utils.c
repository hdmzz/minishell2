#include "../../include/minishell.h"

void	add_cmd_back(t_shell *g_shell, t_cmd *to_add)
{
	t_cmd	*temp;

	temp = g_shell->cmds;
	if (!g_shell->cmds)
	{
		g_shell->cmds = to_add;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
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

	i = 0;
	split_size = count_split_size(token) + 1;///+1 pour le null a la fin
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
		{
			new->cmd[i] = token->value;
			i++;
		}
		token = token->next;
	}
	new->cmd[i] = NULL;
	new->next = NULL;
	new->prev = NULL;
	print_cmd(new->cmd);
	return (new);
}

//void	recompose_cmd(t_shell *g_shell)
//{
//	t_token	*lst;
//	int		pipes_nb;

//	pipes_nb = count_pipes(g_shell->list_token) + 1;
//	g_shell->nb_cmds = pipes_nb;
//	lst = g_shell->list_token;
//	while (pipes_nb--)//on itere sur le nombre de commandes
//	{
//		while (lst->type == pipeline)
//			lst = lst->next;
//		add_cmd_back(g_shell, create_new_cmd(lst));
//		lst = lst->next;
//	}
//}

/* 
	here we are gonna take the list token and create a command node
	based directly on the token no need to split and concat
 */
void	compose_cmd(t_shell *g_shell)
{
	int		pipes_nb;
	t_token	*lst;

	lst = g_shell->list_token;
	pipes_nb = count_pipes(g_shell->list_token) + 1;
	while (pipes_nb--)
	{
		add_cmd_back(g_shell, create_new_cmd(lst));
		while (lst && lst->type != pipeline)
			lst = lst->next;
	}
}
