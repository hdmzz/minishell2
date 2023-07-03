#include "../../include/minishell.h"

//This function is used to concat the words token at the end
t_token	*final_concat(t_token *start)
{
	t_token	*tmp;
	t_token	*new;
	char	*value;
	char	*buff;
	int		type;

	value = ft_strdup("");
	type = start->type;
	tmp = start->next;
	while (tmp->type == type)
	{
		buff = value;
		value = ft_strjoin(value, tmp->value);
		free(buff);
		tmp = tmp->next;
	}
	new = new_token(value, literal, start->pos);
	new->next = tmp;
	new->prev = start->prev;
	delfew(start, tmp->prev);
	return (new);
}
