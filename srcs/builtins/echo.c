#include "../../include/minishell.h"

void	clean_white_spaces(t_token *lst)
{
	t_token	*temp;
	t_token	*buff;

	temp = lst;
	while (temp)
	{
		if (temp->type == pipeline)
		{
			if (temp->prev->type == white_space)
			{
				temp->prev = temp->prev->prev;
				delone(temp->prev);
			}
			if (temp->next->type == white_space)
			{

			}
		}
	}
}
