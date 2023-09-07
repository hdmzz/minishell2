/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:43:43 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/07 14:22:20 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_is_dir(char **cmd)
{
	struct stat	buf;

	ft_bzero(&buf, sizeof(struct stat));
	stat(cmd[0], &buf);
	return (S_ISDIR(buf.st_mode));
}

static int	get_err_num(t_cmd *c)
{
	if (cmd_is_dir(c->cmd))
		return (error_handler(c->cmd[0], NULL, "is a directory", \
		INSUFFICIENT_PERMISSIONS));
	if (access(c->full_cmd_path, F_OK) == -1)
		return (error_handler("command not found", c->cmd[0], NULL, 127));
	else if (access(c->full_cmd_path, X_OK) == -1)
		return (error_handler("permission denied", c->cmd[0], strerror(errno), \
		INSUFFICIENT_PERMISSIONS));
	else if (access(c->full_cmd_path, X_OK | F_OK) != 0)
		return (error_handler(c->cmd[0], NULL, strerror(errno), \
		INSUFFICIENT_PERMISSIONS));
	return (0);
}

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
		return (NULL);
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
	ret = get_err_num(c);
	if (ret != 0)
		return (ret);
	if (execve(full_cmd_path, cmd, NULL) == -1)
	{
		error_handler("execve", NULL, strerror(errno), ret);
		exit_builtin(g_shell, ret);
	}
	return (EXIT_FAILURE);
}
