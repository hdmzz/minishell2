#include "../../include/minishell.h"

void	cln_whitespace_btw_ctrl_tok(t_shell *g_shell)
{
	t_token	*temp;

	temp = g_shell->list_token;
	while (temp)
	{
		if (temp->next && (temp->type & 31))
		{
			while (temp->next && temp->next->type == white_space)
				delone(temp->next);
		}
		if (temp->prev && (temp->type & 31))
		{
			while (temp->prev && temp->prev->type == white_space)
				delone(temp->prev);
		}
		temp = temp->next;
	}
}

int	check_redirection_rules(t_shell *g_shell)
{
	t_token	*temp;

	temp = g_shell->list_token;
	while (temp)
	{
		if (temp->type & 31)//si on est sur un token de controle
		{
			//il faut avancer tant que l'on a des whites space
		}
			return (0);
		temp = temp->next;
	}
	return (1);
}
