/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsilverb <hsilverb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:15:20 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/07 16:50:18 by hsilverb         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "typedef.h"
#include "minishell.h"

int	exit_builtin(t_shell *g_shell, int last_exit)
{
	if (last_exit == 1)
		printf("exit\n");
	ft_free_shell(g_shell, last_exit);
	rl_clear_history();
	exit(last_exit);
}
