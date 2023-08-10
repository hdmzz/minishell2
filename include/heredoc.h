#ifndef HEREDOC_H
# define HEREDOC_H
# include <unistd.h>
# include "typedef.h"

//heredoc.c
int		heredoc(char *delim, t_io *io, t_shell *g_shell);

//heredoc_parser.c
int		heredoc_first_analyzer(t_shell *g_shell);
char	*var_xpanser(char *input);

//exec/exec_heredoc.c
char	*exec_imbricated_cmd(char *cmd_str, ssize_t bytes_read, t_shell *g_shell);

//parser/parser_heredoc.c
char	*heredoc_expanser(char *input, t_io *std_io, t_shell *g_shell);

#endif
