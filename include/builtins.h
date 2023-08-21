#ifndef BUILTINS_H
# define BUILTINS_H
# include "typedef.h"

int	cd_builtin(char **cmd);
int	dispatcher_builtin(t_shell *g_shell, char **cmds);
int	exit_builtin(t_shell *g_shell, int last_exit);
int	export_builtin(char **user_input, t_shell *g_shell);
int	pwd_builtin(void);
int	echo_builtin(char **args);
int	unset_builtin(char **input, t_shell *g_shell);
int	env_builtin(char **cmd, t_shell *g_shell);

#endif
