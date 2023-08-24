#ifndef PIPES_H
# define PIPES_H
# include "typedef.h"

//srcs/exec/pipes.c
int		cmd_handler(t_shell *g_shell);
void	close_fds(int *fd);
void	redir_io(t_cmd *cmds);
#endif
