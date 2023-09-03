/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:16:11 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/03 15:11:44 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	err_msg_len(char *s1, char *s2, char *s3)
{
	int	tot_len;

	tot_len = 0;
	if (s1 != NULL)
		tot_len += ft_strlen(s1);
	if (s2 != NULL)
		tot_len += ft_strlen(s2);
	if (s3 != NULL)
		tot_len += ft_strlen(s3);
	return (tot_len);
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
	int		total_len;

	total_len = err_msg_len(cmd, detail, "minishell: ") + 4;
	msg = ft_calloc(total_len + 6, sizeof(char));
	if (cmd != NULL)
		detail_quotes = export_or_unset(cmd);
	if (cmd != NULL)
		ft_vsprintf(msg, "minishell: %s:", cmd);
	if (detail != NULL)
	{
		if (detail_quotes)
			ft_vsprintf(msg, "%s`%s':", msg, detail);
		ft_vsprintf(msg, "%s %s:", msg, detail);
	}
	ft_vsprintf(msg, "%s %s", msg, err_msg);
	ft_putendl_fd(msg, STDERR_FILENO);
	msg = ft_free_ptr(msg);
	return (err_nb);
}

int	error_parsing_handler(char *err, char *detail, int err_nb, int quotes)
{	
	char	*msg;
	int		total_len;

	total_len = err_msg_len(err, detail, "minishell: ") + 5;
	msg = ft_calloc(total_len, sizeof(char));
	if (!msg)
		return (0);
	if (quotes)
		ft_vsprintf(msg, "minishell: %s: `%s'", err, detail);
	ft_vsprintf(msg, "minishell: %s: %s", err, detail);
	ft_putendl_fd(msg, STDERR_FILENO);
	msg = ft_free_ptr(msg);
	return (err_nb);
}
