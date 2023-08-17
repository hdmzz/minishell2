/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:48:11 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/17 19:18:16 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_last_exit_code = 0;

static int	check_start(int ac, char **av)
{
	if (ac != 1 && av[0])
		return (0);
	return (1);
}

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

static int	init_g_shell(t_shell *g_shell, t_cmd *start_cmd, char **env)
{
	ft_memset(g_shell, 0, sizeof(t_shell));
	ft_memset(start_cmd, 0, sizeof(t_cmd));
	g_shell->output_backup = dup(STDOUT_FILENO);
	g_shell->input_backup = dup(STDIN_FILENO);
	g_shell->io = ft_calloc(1, sizeof(t_io));//leaks ici
	g_shell->start_token = new_token("", 513, 0);
	if (!g_shell->io)
		return (0);
	g_shell->split_env = env;
	return (1);
}

//il faut recuperer la commande donc faire un split et ensuite executer
int	main(int ac, char **av, char **env)
{
	t_cmd	start_cmd;
	t_shell	g_shell;

	if (!check_start(ac, av))
		return (1);
	if (!init_g_shell(&g_shell, &start_cmd, env))
		return (perror("Error init shell\n"), 1);
	g_shell.start_cmd = &start_cmd;
	prompt(&g_shell);
	return (0);
}
