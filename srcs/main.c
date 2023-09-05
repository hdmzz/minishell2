/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:48:11 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/05 04:35:09 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (parser(g_shell) == EXIT_FAILURE)
			g_last_exit_code = 1;
		else
			g_last_exit_code = cmd_handler(g_shell);
		ft_free_shell(g_shell, 0);
	}
}

static int	init_g_shell(t_shell *g, t_cmd *start_cmd, t_token *tok, char **env)
{
	int	i;

	i = -1;
	ft_memset(g, 0, sizeof(t_shell));
	ft_memset(start_cmd, 0, sizeof(t_cmd));
	tok->type = 513;
	tok->pos = 0;
	start_cmd->idx_cmd = -1;
	g->output_backup = dup(STDOUT_FILENO);
	g->input_backup = dup(STDIN_FILENO);
	g->start_token = tok;
	g->split_env = ft_calloc(split_lenght(env) + 1, sizeof(char *));
	if (g->split_env == NULL)
		return (0);
	while (env[++i])
		g->split_env[i] = ft_strdup(env[i]);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_cmd	start_cmd;
	t_shell	g_shell;
	t_token	start_token;

	ft_memset(&start_token, 0, sizeof(t_token));
	if (!check_start(ac, av))
		return (EXIT_SUCCESS);
	if (!init_g_shell(&g_shell, &start_cmd, &start_token, env))
		return (perror("Error init shell\n"), 1);
	g_shell.start_cmd = &start_cmd;
	prompt(&g_shell);
	ft_free_ptr(g_shell.start_token);
	return (0);
}
