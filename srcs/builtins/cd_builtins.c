/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsilverb <hsilverb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:18:44 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/07 16:50:03 by hsilverb         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *name, t_shell *g_shell)
{
	char	*value;
	int		indx;

	indx = get_env_idx(name, g_shell);
	if (indx == -1)
		return (NULL);
	value = g_shell->split_env[indx];
	value = ft_strchr(value, '=') + 1;
	return (value);
}

int	get_env_idx(const char *name, t_shell *g_shell)
{
	int		i;
	char	*buff;
	char	**env;

	i = 0;
	buff = ft_strjoin(name, "=");
	env = g_shell->split_env;
	while (env[i])
	{
		if (ft_strncmp(buff, env[i], ft_strlen(buff)) == 0)
			return (ft_free_ptr(buff), i);
		i++;
	}
	return (ft_free_ptr(buff), -1);
}

static int	change_dir(char	*path, t_shell *g_shell)
{
	char	*cwd;
	char	buff[PATH_MAX];

	cwd = getcwd(buff, PATH_MAX);
	if (!cwd || !path)
		return (EXIT_FAILURE);
	if (chdir(path) == -1)
		return (error_handler("cd", path, strerror(errno), EXIT_FAILURE));
	my_set_env("OLD_PWD", get_env_value("PWD", g_shell), g_shell);
	my_set_env("PWD", cwd, g_shell);
	return (EXIT_SUCCESS);
}

int	cd_builtin(t_cmd *c, t_shell *g_shell)
{
	int	len;

	len = split_lenght(c->cmd);
	if (len > 2)
		return (error_handler("cd", NULL, " too many arguments", 1));
	else if (len == 1)
		return (change_dir(get_env_value("HOME", g_shell), g_shell));
	else if (len == 2 && !ft_strcmp(c->cmd[1], "-"))
		return (change_dir(get_env_value("OLD_PWD", g_shell), g_shell));
	return (change_dir(c->cmd[1], g_shell));
}
