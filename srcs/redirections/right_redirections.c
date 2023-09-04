/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:23:47 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/04 12:23:48 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	right_redirections(t_cmd *cmds, int split_lght)
{
	int		i;
	int		fd;
	int		oflag;
	char	**cmd;

	i = 0;
	oflag = O_WRONLY | O_CREAT | O_TRUNC;
	cmd = cmds->cmd;
	while (i < split_lght)
	{
		if (cmd[i][0] == '>' && ft_strlen(cmd[i]) <= 2)
		{
			if (!ft_strcmp(cmd[i], ">>"))
				oflag = O_WRONLY | O_APPEND | O_CREAT;
			fd = open(cmd[i + 1], oflag, 0644);
			if (fd == -1)
				return (-1);
			cmds->output_backup = dup(STDOUT_FILENO);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			cmd[i] = NULL;
			cmd[i + 1] = NULL;
			i++;
		}
		i++;
	}
	return (1);
}
