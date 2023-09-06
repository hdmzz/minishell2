/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:43:43 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/06 15:02:21 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cmd_util(char **split_env, char **to_search)
{
	int		i;
	char	*cmd;
	char	*full_cmd;

	i = -1;
	cmd = ft_strjoin("/", to_search[0]);
	if (!cmd)
		return (NULL);
	while (split_env[++i])
	{
		full_cmd = ft_strjoin(split_env[i], cmd);
		if (!access(full_cmd, X_OK))
			return (ft_free_ptr(cmd), full_cmd);
		full_cmd = ft_free_ptr(full_cmd);
	}
	cmd = ft_free_ptr(cmd);
	return (NULL);
}

char	*get_cmd_path(char **to_search, t_shell *g_shell)
{
	char	**split_env;
	char	*full_cmd_path;
	int		path_indx;

	path_indx = get_env_idx("PATH", g_shell);
	if (!access(to_search[0], X_OK))
		return (to_search[0]);
	if (path_indx == -1)
	{
		//error_handler(to_search[0], "command not found", NULL, 0);
		return (NULL);
	}
	split_env = ft_split(g_shell->split_env[path_indx], ':');
	full_cmd_path = get_cmd_util(split_env, to_search);
	if (full_cmd_path != NULL)
		return (ft_free_split(split_env), full_cmd_path);
	ft_free_split(split_env);
	ft_free_ptr(full_cmd_path);
	return (NULL);
}

int	exec_cmd(char **cmd, t_cmd *c, t_shell *g_shell)
{
	char	*full_cmd_path;
	int		ret;

	full_cmd_path = c->full_cmd_path;
	if (full_cmd_path == NULL)
	{
		return (error_handler(cmd[0], NULL, "command not found", COMMAND_NOT_FOUND));
	}
	ret = execve(full_cmd_path, cmd, NULL);
	error_handler("execve", NULL, strerror(errno), ret);
	exit_builtin(g_shell, ret);
	return (ret);
}
