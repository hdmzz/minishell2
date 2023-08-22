#ifndef BUILTINS_H
# define BUILTINS_H
# include "typedef.h"

int	cd_builtin(char **cmd);
int	dispatcher_builtin(t_shell *g_shell, t_cmd *c);
int	exit_builtin(t_shell *g_shell, int last_exit);
int	export_builtin(t_cmd *c, t_shell *g_shell);
int	pwd_builtin(void);
int	echo_builtin(char **args);
int	unset_builtin(char **input, t_shell *g_shell);
int	env_builtin(char **cmd, t_shell *g_shell);

#endif
