/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 02:55:02 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/24 07:33:21 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//int	left_redirections(t_cmd *cmds, int split_lght)
//{
//	int		i;
//	int		fd;
//	char	**cmd;

//	i = -1;
//	cmd = cmds->cmd;
//	if (!cmd)
//		return (1);
//	while (++i < split_lght)
//	{
//		if (cmd[i][0] == '<')
//		{
//			if (ft_strcmp(cmd[i], "<<") == 0)
//				fd = heredoc(cmd);
//			else
//				fd = open(cmd[i + 1], O_RDONLY, NULL);
//			if (fd == -1)
//				return (0);
//			cmds->input_backup = dup(STDIN_FILENO);
//			dup2(fd, STDIN_FILENO);
//			close(fd);
//			cmd[i] = NULL;
//			cmd[i + 1] = NULL;
//			i++;
//		}
//	}
//	return (1);
//}
