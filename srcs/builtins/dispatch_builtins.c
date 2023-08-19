#include "minishell.h"

int	dispatcher_builtin(t_shell *g_shell, char **cmds)
{
	if (ft_strcmp("export", cmds[0]) == 0)
		export_builtin(cmds, g_shell);
	else if (ft_strcmp("exit", cmds[0]) == 0)
		return (exit_builtin(g_shell));
	//else if (ft_strcmp("echo", cmd[0]) == 0)
	//	return (echo_builtin(cmds, g_shell));
	//else if (ft_strcmp("cd", cmd[0]) == 0)
	//	return (cd_builtin(cmd));
	//else if (ft_strcmp("pwd", cmd[0]) == 0)
	//	return (pwd(cmd));
	//else if (ft_strcmp("unset", cmd[0]) == 0)
	//	return (unset(cmd));
	//else if (ft_strcmp(env, cmd[0]) == 0)
	//	return (env(cmd));
	return (1);
}
