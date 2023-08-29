/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:16:11 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/28 19:22:17 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_shell(char *s, char *to_add)
{
	char	*tmp;

	if (!to_add)
		return (s);
	if (!s)
		return (ft_strdup(to_add));
	tmp = s;
	s = ft_strjoin(tmp, to_add);
	tmp = ft_free_ptr(tmp);
	return (s);
}

//fonction qui dis si oui 
static int	export_or_unset(char *cmd)
{
	if (ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

int	error_handler(char *cmd, char *detail, char *err_msg, int err_nb)
{
	char	*msg;
	int		detail_quotes;

	detail_quotes = export_or_unset(cmd);
	msg = ft_strdup("minishell: ");
	if (cmd != NULL)
	{
		msg = ft_join_shell(msg, cmd);
		msg = ft_join_shell(msg, ": ");
	}
	if (detail != NULL)
	{
		if (detail_quotes)
			msg = ft_join_shell(msg, "`");
		msg = ft_join_shell(msg, detail);
		if (detail_quotes)
			msg = ft_join_shell(msg, "'");
		msg = ft_join_shell(msg, ": ");
	}
	msg = ft_join_shell(msg, err_msg);
	ft_putendl_fd(msg, STDERR_FILENO);
	msg = ft_free_ptr(msg);
	return (err_nb);
}

