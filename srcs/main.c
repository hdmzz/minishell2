/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:48:11 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/13 18:10:52 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_last_exit_code = 0;

void	prompt(t_shell *g_shell)
{
	while (isatty(STDIN_FILENO))
	{
		set_signals_interactive();
		g_shell->start_buff = readline("$> ");
		set_signals_noninteractive();
		lexer(g_shell);
		if (!parser(g_shell))
			printf("Error parsing");
		ft_free_shell(g_shell, 0);
		free(g_shell->start_buff);
	}
}

static int	init_g_shell(t_shell *g_shell)
{
	g_shell->start_buff = NULL;
	g_shell->full_cmd_path = NULL;
	g_shell->splitted_cmd = NULL;
	g_shell->split_env = NULL;
	g_shell->list_token = NULL;
	g_shell->cmds = NULL;
	g_shell->output_backup = dup(STDOUT_FILENO);
	g_shell->input_backup = dup(STDIN_FILENO);
	g_shell->io = ft_calloc(1, sizeof(t_io));//leaks ici
	g_shell->start_token = new_token("", 513, 0);
	if (!g_shell->io)
		return (0);
	g_shell->io->delim_in_quotes = 0;
	g_shell->io->var_expanser = 0;
	g_shell->pids = NULL;
	g_shell->nb_pipes = 0;
	g_shell->pipes_fd = NULL;
	return (1);
}

//il faut recuperer la commande donc faire un split et ensuite executer
int	main(void)
{
	t_cmd	start_cmd;
	t_shell	g_shell;

	start_cmd.cmd = NULL;
	start_cmd.next = NULL;
	start_cmd.prev = NULL;
	start_cmd.nb_of_cmd = 0;

	if (!init_g_shell(&g_shell))
		return (perror("Error init shell\n"), 1);
	g_shell.start_cmd = &start_cmd;
	prompt(&g_shell);
	return (0);
}
