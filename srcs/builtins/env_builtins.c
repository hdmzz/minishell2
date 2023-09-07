/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsilverb <hsilverb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:15:14 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/07 16:31:29 by hsilverb         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_builtin(char **cmd, t_shell *g_shell)
{
	int	i;

	i = 0;
	if (split_lenght(cmd) > 1)
		return (EXIT_FAILURE);
	if (g_shell->split_env == NULL)
		return (EXIT_FAILURE);
	while (g_shell->split_env[i])
	{
		printf("%s\n", g_shell->split_env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
