/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 03:15:14 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/24 05:58:46 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	heredoc(t_cmd *c)
{
	char	*tmp;
	char	*input;

	while (1)
	{
 		input = readline("> ");
		if (ft_strcmp(c->heredoc_delim, input) == 0)
			break ;
		tmp = heredoc_expanser(input, c, -1, 0);
		if (!tmp)
			return (ft_free_ptr(input), 0);
		ft_putendl_fd(tmp, c->fd_heredoc);
		if (c->hd_delim_into_quotes)
			tmp = ft_free_ptr(tmp);
	}
	return (close(c->fd_heredoc), 1);
}
