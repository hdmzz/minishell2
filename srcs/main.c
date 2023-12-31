/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:48:11 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/24 10:16:16 by hdamitzi         ###   ########.fr       */
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
			printf("Error parsing\n");
		ft_free_shell(g_shell, 0);
		free(g_shell->start_buff);
	}
}

static int	init_g_shell(t_shell *g_shell, t_cmd *start_cmd, char **env)
{
	int	i;

	i = -1;
	ft_memset(g_shell, 0, sizeof(t_shell));
	ft_memset(start_cmd, 0, sizeof(t_cmd));
	start_cmd->idx_cmd = -1;
	g_shell->output_backup = dup(STDOUT_FILENO);
	g_shell->input_backup = dup(STDIN_FILENO);
	g_shell->start_token = new_token("", 513, 0);
	g_shell->split_env = ft_calloc(split_lenght(env) + 1, sizeof(char *));
	if (g_shell->split_env == NULL)
		return (0);
	while (env[++i])
		g_shell->split_env[i] = ft_strdup(env[i]);//
	return (1);
}

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
	ft_free_ptr(g_shell.start_token);
	return (0);
}
