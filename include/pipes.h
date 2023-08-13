#ifndef PIPES_H
# define PIPES_H
# include "typedef.h"

//srcs/exec/pipes.c
int		cmd_handler(t_shell *g_shell);
void	close_fds(int **fds, int nb_pipes, int i);
#endif
