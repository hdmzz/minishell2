/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 01:57:42 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/28 02:02:35 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedef.h"

void	free_pipes(t_shell *g_shell);
void	restore_io(t_cmd *cmds);
void	close_cmds_fds(t_cmd *c);
void	close_pipes_fds(t_cmd *cmds, t_cmd *cur);

