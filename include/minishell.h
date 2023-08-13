/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:45:59 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/13 13:31:28 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "typedef.h"
# include "builtins.h"
# include "pipes.h"
# include "signal_sh.h"

//srcs/parser/parser.c
int		parser(t_shell *g_shell);
void	dollar_rule(t_shell *g_shell);

//parser_utils.c
void	compose_cmd(t_shell *g_shell);

//srcs/exec/exec.c
int		exec_cmd(char **cmd, t_shell *g_shell);
char	*get_cmd_path(char **to_search);

//srcs/lexer/lexer.c
int	lexer(t_shell *g_shell);

//src/utils/utils.c
void	ft_free_shell(t_shell *g_shell, int last_exit);
void	del_cmds(t_cmd *cmds);
int		split_lenght(char **cmds);

//src/lexer/token_utils.c
t_token	*new_token(char *value, int type, int pos);
void	token_add_back(t_token **lst, t_token *to_add);
t_token	*last_token(t_token *token);
void	quotes_neutralizer(t_token **lst);
t_token	*replace_token(t_token *start, t_token *end, t_token *new);

//src/lexer/token_utils2.c
t_token	*final_concat(t_token *start);
t_token	*concat_token(t_token *start);
void	delfew(t_token *start, t_token *end);
void	delone(t_token *to_del);
int		concat_word(t_shell *g_shell);

//src/lexer/token_utils3.c
void	cln_whitespace_btw_ctrl_tok(t_shell *g_shell);
int		check_redirection_rules(t_shell *g_shell);

//src/error/error.c
void	error_handler(char *error);

//pipes_conformity.c
bool	pipes_conformity(t_shell *g_shell);

//buiding function
void	print_lst(t_token *token);
void	print_cmd(char **cmds);

//redir.c
void	clean_cmd_tab(char **cmd, int first_redir, int end);
int		recover_fd(t_shell *g_shelll);
int		redirections(t_shell *g_shell);

//simple_right.c > output redir
int		right_redirections(char **cmd, int split_lght);

//simple_left.c < input redir
int		left_redirections(char **cmd, int split_lght, t_shell *g_shell);

//heredoc.c
int		heredoc(char *delim, t_io *io);

//heredoc_parser.c
int		heredoc_first_analyzer(t_shell *g_shell);
char	*var_xpanser(char *input);

//exec/exec_heredoc.c
char	*exec_imbricated_cmd(char *cmd_str, ssize_t bytes_read);

//parser/parser_heredoc.c
char	*heredoc_expanser(char *input, t_io *std_io);


#endif
