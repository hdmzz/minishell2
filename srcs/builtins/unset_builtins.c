/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsilverb <hsilverb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:16:05 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/07 16:50:28 by hsilverb         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	remove_var(int idx, t_shell *g_shell)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = ft_calloc(split_lenght(g_shell->split_env), sizeof(char *));
	if (new_env == NULL)
		return (EXIT_FAILURE);
	while (g_shell->split_env[i])
	{
		if (i != idx)
		{
			new_env[j] = ft_strdup(g_shell->split_env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	ft_free_split(g_shell->split_env);
	g_shell->split_env = NULL;
	g_shell->split_env = new_env;
	return (EXIT_SUCCESS);
}

int	unset_builtin(t_cmd *c, t_shell *g_shell)
{
	int		idx;
	int		i;
	int		ret;
	char	**cmd;

	cmd = c->cmd;
	i = 1;
	ret = EXIT_SUCCESS;
	while (cmd[i])
	{
		if (is_valid_env_var_key(cmd[i]) == 0 || ft_strchr(cmd[i], '=') != NULL)
			return (0);
		else
		{
			idx = get_env_idx(cmd[i], g_shell);
			if (idx != -1)
				ret = remove_var(idx, g_shell);
		}
		i++;
	}
	return (ret);
}
