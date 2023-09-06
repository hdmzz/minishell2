/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:45:59 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/06 14:33:23 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "typedef.h"
# include "builtins.h"
# include "pipes.h"
# include "signal_sh.h"
# include "heredoc.h"

//srcs/parser/parser.c
int		parser(t_shell *g_shell);
void	dollar_rule(t_shell *g_shell, t_token *lst, int quote_count);

//parser_utils.c
void	compose_cmd(t_shell *g_shell);

//srcs/exec/exec.c
int		exec_cmd(char **cmd, t_cmd *c, t_shell *g_shell);
char	*get_cmd_path(char **to_search, t_shell *g_shell);

//srcs/lexer/lexer.c
int		lexer(t_shell *g_shell);

//src/utils/utils.c
void	ft_free_shell(t_shell *g_shell, int last_exit);
void	del_cmds(t_cmd *cmds);
int		split_lenght(char **cmds);

//src/lexer/token_utils.c
t_token	*new_token(char *value, int type, int pos);
void	token_add_back(t_token **lst, t_token *to_add);
t_token	*last_token(t_token *token);
void	quotes_neutralizer(t_shell *g_shell);
t_token	*replace_token(t_token *start, t_token *end, t_token *new);

//src/lexer/token_utils2.c
t_token	*final_concat(t_token *start);
t_token	*concat_token(t_token *start);
void	delfew(t_token *start, t_token *end);
void	*delone(t_token *to_del);
int		concat_word(t_shell *g_shell);

//src/lexer/token_utils3.c
void	cln_whitespace_btw_ctrl_tok(t_shell *g_shell);
int		check_redirection_rules(t_shell *g_shell);

//src/error/error.c
int		error_handler(char *cmd, char *detail, char *err_msg, int err_nb);
int		error_parsing_handler(char *err, char *detail, int err_nb, int quotes);

//pipes_conformity.c
bool	pipes_conformity(t_shell *g_shell);

//redir.c
void	clean_cmd_tab(char **cmd, int first_redir, int end);
int		recover_fd(t_shell *g_shelll);
void	recover_or_io(t_cmd *cmd);
void	redir_io(t_cmd *c);

//cleanup.c
void	close_fds(int *fd);
void	close_pipes_fds(t_cmd *cmds, t_cmd *cur);
void	free_pipes(t_shell *g_shell);
void	close_cmds_fds(t_cmd *c);
void	restore_io(t_cmd *cmds);

//pipes_utils.c
int		prepare_pipes_for_exec(t_shell *g_shell);
int		set_pipes(t_cmd *c, t_shell *g);
int		init_pipes(t_cmd *c);
void	create_pipe(int *pipefd);

//quotes_utils.c
t_token	*quotes_appared(t_token *first_quote);
bool	quotes_rules(t_token *token);

t_token	*conc_lit(t_token *next, char *value, int pos);
t_token	*concat_literals(t_token *start, t_token *cur, \
t_token *buff, char *tmp);

char	*recompose_input(char **tab);
char	*substitute_input_wth_output(char *input, char *cmd_output);

//utils.c
void	*free_lst_token(t_token *tokens);
char	*ev_expander(t_token *l);

#endif
