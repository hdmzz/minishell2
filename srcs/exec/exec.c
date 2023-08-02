/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:43:43 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/01 13:20:57 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 
*	strlcat of the dir name + / + entrypath(the command name like ls) + \0
 */
static char	*concat_cmd(char *dir_path, char *entry_path)
{
	char	*cmd;
	int		total_lenght;

	total_lenght = ft_strlen(dir_path) + ft_strlen(entry_path) + 2;
	cmd = ft_calloc(sizeof(char), total_lenght);
	if (!cmd)
		return (NULL);
	ft_strlcat(cmd, dir_path, total_lenght);
	ft_strlcat(cmd, "/", total_lenght);
	ft_strlcat(cmd, entry_path, total_lenght);
	return (cmd);
}

static bool	found_cmd_path(char *cmd, char *to_comp)
{
	if (ft_strncmp(cmd, to_comp, ft_strlen(to_comp)) == 0)
		return (true);
	return (false);
}

//58 is int for : in ascii
char	*get_cmd_path(char **to_search)
{
	char			**split_env;
	DIR				*dir;
	struct dirent	*entry;
	int				i;

	i = -1;
	if (!access(to_search[0], X_OK))
		return (to_search[0]);
	split_env = ft_split(getenv("PATH"), 58);
	while (split_env[++i])
	{
		dir = opendir(split_env[i]);
		if (dir != NULL)
		{
			entry = readdir(dir);
			while ((entry = readdir(dir)) != NULL)
			{
				if (found_cmd_path(to_search[0], entry->d_name) == true)
					return (concat_cmd(split_env[i], entry->d_name));
			}
		}
		closedir(dir);
	}
	return (NULL);
}

int	exec_cmd(char **cmd)
{
	pid_t	pid;
	char	*full_cmd_path;

	full_cmd_path = get_cmd_path(cmd);
	if (full_cmd_path == NULL)
		return (perror("Getenv"), 0);
	pid = fork();
	if (pid == -1)
		return (perror("Fork issue"), 0);
	if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		kill(pid, SIGTERM);
		free(full_cmd_path);
	}
	else if (pid == 0)
	{
		if ((execve(full_cmd_path, cmd, NULL)) == -1)
			return (perror("Exec"), 0);
	}
	return (1);
}
