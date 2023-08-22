#include "minishell.h"

int	dispatcher_builtin(t_shell *g_shell,t_cmd *c)
{
	if (ft_strcmp("export", c->cmd[0]) == 0)
		return(export_builtin(c, g_shell));
	else if (ft_strcmp("exit", c->cmd[0]) == 0)
		return(exit_builtin(g_shell, 1));
	else if (ft_strcmp("echo", c->cmd[0]) == 0)
		return (echo_builtin(c->cmd));
	else if (ft_strcmp("env", c->cmd[0]) == 0)
		return (env_builtin(c->cmd, g_shell));
	//else if (ft_strcmp("cd", cmd[0]) == 0)
	//	return (cd_builtin(cmd));
	//else if (ft_strcmp("pwd", cmd[0]) == 0)
	//	return (pwd(cmd));
	//else if (ft_strcmp("unset", cmd[0]) == 0)
	//	return (unset(cmd));
	return (0);
}
