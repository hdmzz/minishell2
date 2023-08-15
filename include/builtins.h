#ifndef BUILTINS_H
# define BUILTINS_H
# include "typedef.h"

int	cd_builtin(char **cmd);
int	dispatcher_builtin(t_shell *g_shell, char **cmds);
int	exit_builtin(t_shell *g_shell);
int	export_builtin(char **user_input);
int	pwd_builtin(t_cmd *cmds);
int	echo_builtin(char **args, t_shell *g_shell);
int	unset_builtin(char **input, t_shell *g_shell);


#endif
