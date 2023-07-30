#include "../../include/minishell.h"

int	check_delim(t_token *lst)
{
	while (lst->type == white_space)
		lst = lst->next;
	//on arricve soi sur un literal soit sur une doublequote
	if (lst->type == literal)
		return (1);
	
}

int	heredoc_parser(t_shell *g_shell)
{
	t_token	*lst;

	lst = g_shell->list_token;
	while (lst)
	{
		if (lst->type == double_redir_left)//on a un heredoc
		{
			if (check_delim(lst))
				g_shell->io->delim_in_quotes = 1;
		}
	}
}
