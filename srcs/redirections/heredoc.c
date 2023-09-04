/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 03:15:14 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/04 17:08:42 by hdamitzi         ###   ########.fr       */
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
		if (c->hd_delim_into_quotes == 0)
			tmp = heredoc_expanser(input, c, -1, 0);
		else
			tmp = input;
		if (!tmp)
			return (input = ft_free_ptr(input), 0);
		ft_putendl_fd(tmp, c->fd_heredoc);
	}
	close(c->fd_heredoc);
	c->heredoc = 0;
	return (1);
}
