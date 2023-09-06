/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 03:15:14 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/06 17:15:41 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(t_cmd *c)
{
	char	*tmp;
	int		ret;

	while (1)
	{
		set_signals_interactive();
		tmp = readline("> ");
		set_signals_noninteractive();
		if (tmp == NULL)
		{
			ret = error_handler("warning", \
			"here doc delimited by end of file wanted", c->heredoc_delim, 0);
			break ;
		}
		if (ft_strcmp(c->heredoc_delim, tmp) == 0)
			return (close(c->fd_heredoc), tmp = ft_free_ptr(tmp), 1);
		if (c->hd_delim_into_quotes == 0)
			tmp = heredoc_expanser(tmp, c, -1, 0);
		if (!tmp)
			return (tmp = ft_free_ptr(tmp), 0);
		ft_putendl_fd(tmp, c->fd_heredoc);
		tmp = ft_free_ptr(tmp);
	}
	close(c->fd_heredoc);
	return (ret);
}
