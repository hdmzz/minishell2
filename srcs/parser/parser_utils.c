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

t_cmd	*create_new_cmd(t_token *token)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = ft_split_charset(token->value, " \t\n");
	new->next = NULL;
	new->prev = NULL;
	return (new);
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

void	recompose_cmd(t_shell *g_shell)
{
	t_token	*lst;
	int		pipes_nb;

	pipes_nb = count_pipes(g_shell->list_token) + 1;
	lst = g_shell->list_token;
	while (pipes_nb--)//on itere sur le nombre de commandes
	{
		while (lst->type == pipeline)
			lst = lst->next;
		add_cmd_back(g_shell, create_new_cmd(lst));
		lst = lst->next;
	}
}
