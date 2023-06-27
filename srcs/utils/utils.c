/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:38:17 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/15 13:41:27 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_shell(t_shell *g_shell)
{
	if (g_shell->full_cmd_path != NULL)
		free(g_shell->full_cmd_path);
	if (g_shell->splitted_cmd != NULL)
		ft_free_split(g_shell->splitted_cmd);
	if (g_shell->start_buff != NULL)
		free(g_shell->start_buff);
}
