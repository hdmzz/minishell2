/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:48:11 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/06 13:53:40 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	init_g_shell(t_shell *g_shell)
{
	g_shell->start_buff = NULL;
	g_shell->full_cmd_path = NULL;
	g_shell->splitted_cmd = NULL;
	g_shell->list_token = NULL;
	g_shell->start_token = NULL;
	g_shell->cmds = NULL;
	g_shell->output_backup = dup(STDOUT_FILENO);
	g_shell->input_backup = dup(STDIN_FILENO);
	g_shell->io = malloc(sizeof(t_io));
	if (!g_shell->io)
		return (0);
	g_shell->io->delim_in_quotes = 0;
	g_shell->io->var_expanser = 0;
	g_shell->split_env = NULL;
	g_shell->pids = NULL;
	g_shell->nb_pipes = 0;
	return (1);
}

//il faut recuperer la commande donc faire un split et ensuite executer
int	main(void)
{
	t_shell	g_shell;

	if (!init_g_shell(&g_shell))
		return (perror("Error init shell\n"), 1);
	g_shell.start_buff = ft_calloc(sizeof(char), 2048);
	if (!g_shell.start_buff)
		return (perror("Error callo\n"), 1);
	while (isatty(STDIN_FILENO))
	{
		g_shell.start_buff = readline("$> ");
		g_shell.list_token = lexer(&g_shell);
		if (!parser(&g_shell))
			printf("Error parsing");
		ft_free_shell(&g_shell);
	}
	return (0);
}
