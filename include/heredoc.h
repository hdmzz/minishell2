#ifndef HEREDOC_H
# define HEREDOC_H
# include <unistd.h>
# include "typedef.h"

//heredoc.c
int		heredoc(t_cmd *c);

//heredoc_parser.c
int		heredoc_first_analyzer(t_shell *g_shell);
char	*var_xpanser(char *input);

int		prepare_io(t_cmd *c);

//exec/exec_heredoc.c
char	*exec_imbricated_cmd(char *cmd_str, ssize_t bytes_read);

//parser/parser_heredoc.c
char	*heredoc_expanser(char *input, t_cmd *c, int i, int y);

//heredoc.c

//heredoc_parser.c
int		heredoc_first_analyzer(t_shell *g_shell);
char	*var_xpanser(char *input);

//exec/exec_heredoc.c
char	*exec_imbricated_cmd(char *cmd_str, ssize_t bytes_read);

#endif
