#include "minishell.h"

static void	child(t_cmd *c, t_shell *g_shell)
{
	if (g_shell->nb_cmds > 1)
		set_pipes(c, g_shell);
	redir_io(c);
	if (dispatcher_builtin(g_shell, c) == 0)
		exec_cmd(c->cmd, c, g_shell);
	exit_builtin(g_shell, 0);
}

static int	handle_pipes_cmd(t_shell *g_shell)
{
	t_cmd	*cmds;
	int		i;

	i = 0;
	cmds = g_shell->cmds;
	while (i < g_shell->nb_cmds)
	{
		g_shell->pids[i] = fork();
		if (g_shell->pids[i] < 0)
			return (0);
		if (g_shell->pids[i] == 0)
			child(cmds, g_shell);
		i++;
		cmds = cmds->next;
	}
	close_cmds_fds(g_shell->cmds);
	i = -1;
	while (++i < g_shell->nb_cmds)
		waitpid(g_shell->pids[i], &g_last_exit_code, 0);
	free_pipes(g_shell);
	return (1);
}

static int	handle_cmd(t_shell *g_shell)
{
	t_cmd	*c;
	int		ret;
	int		pid;

	c = g_shell->cmds;
	pid = -1;
	redir_io(c);
	ret = dispatcher_builtin(g_shell, c);
	restore_io(c);
	if (ret == 0)
	{
		pid = fork();
		if (pid < 0)
			return (0);
		if (pid == 0)
			child(c, g_shell);
	}
	waitpid(pid, &g_last_exit_code, 0);
	return (1);
}

/* 
	This function takes the cmds and execute it with the pipes etc
 */
int	cmd_handler(t_shell *g_shell)
{
	if (g_shell->nb_cmds == 1)
		return(handle_cmd(g_shell));
	else
	{
		prepare_pipes_for_exec(g_shell);
		return(handle_pipes_cmd(g_shell));
	}
	return (1);
}
