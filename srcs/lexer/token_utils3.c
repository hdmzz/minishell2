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
