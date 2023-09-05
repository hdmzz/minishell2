/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 03:15:14 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/06 00:49:02 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(t_cmd *c)
{
	char	*tmp;

	while (1)
	{
		tmp = readline("> ");
		if (ft_strcmp(c->heredoc_delim, tmp) == 0)
			break ;
		if (c->hd_delim_into_quotes == 0)
			tmp = heredoc_expanser(tmp, c, -1, 0);
		if (!tmp)
			return (tmp = ft_free_ptr(tmp), 0);
		ft_putendl_fd(tmp, c->fd_heredoc);
		tmp = ft_free_ptr(tmp);
	}
	close(c->fd_heredoc);
	tmp = ft_free_ptr(tmp);
	c->heredoc = 0;
	return (1);
}
