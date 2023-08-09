/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:43:43 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/09 16:04:32 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (ft_strcmp(cmd, to_comp) == 0)
		return (true);
	return (false);
}

static char	*get_cmd_util(char **split_env, char **to_search)
{
	int				i;
	DIR				*dir;
	struct dirent	*entry;
	char			*full_cmd_path;

	i = -1;
	while (split_env[++i])
	{
		dir = opendir(split_env[i]);
		if (dir != NULL)
		{
			entry = readdir(dir);
			while ((entry = readdir(dir)) != NULL)
			{
				if (found_cmd_path(to_search[0], entry->d_name) == true)
				{
					full_cmd_path = concat_cmd(split_env[i], entry->d_name);
					return (full_cmd_path);
				}
			}
		}
		closedir(dir);
	}
	return (NULL);
}

//58 is int for : in ascii
char	*get_cmd_path(char **to_search)
{
	char			**split_env;
	char			*full_cmd_path;

	if (!access(to_search[0], X_OK))
		return (to_search[0]);
	split_env = ft_split(getenv("PATH"), 58);
	full_cmd_path = get_cmd_util(split_env, to_search);
	if (full_cmd_path != NULL)
		return (ft_free_split(split_env), full_cmd_path);
	if (split_env)
		free(split_env);
	return (NULL);
}

//le exec commd ne devrait pas fork puisque le pipe handler fork lui meme
int	exec_cmd(char **cmd, t_shell *g_shell)
{
	char	*full_cmd_path;

	full_cmd_path = g_shell->full_cmd_path;
	if (full_cmd_path == NULL)
		return (perror("Getenv"), 0);
	if ((execve(full_cmd_path, cmd, NULL)) == -1)
		return (perror("Exec"), 0);
	return(0);
}
