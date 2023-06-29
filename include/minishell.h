/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:45:59 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/29 05:01:37 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <stdbool.h>

enum e_type
{
	new_line,
	white_space,
	pipeline,
	single_quote,
	double_quote,
	simple_redir_left,
	simple_redir_right,
	double_redir_left,
	double_redir_right,
	dollar,
	literal,
};

typedef struct s_token_trslte
{
	char	*value;
	int		type;
	char	*translation;
}			t_token_trslte;

typedef struct s_token
{
	char			*value;
	int				pos;
	int				type;
	struct s_token	*next;
}				t_token;

typedef struct s_shell
{
	char	*start_buff;
	char	*full_cmd_path;
	char	**splitted_cmd;
	t_token	*list_token;
}				t_shell;

//srcs/parser/parser.c
int		parser(t_shell *g_shell);

//srcs/exec/exec.c
void	exec(t_shell *g_shell);

//srcs/lexer/lexer.c
t_token	*lexer(t_shell *g_shell);

//src/utils/utils.c
void	ft_free_shell(t_shell *g_shell);

//src/lexer/token_utils.c
t_token	*new_token(char *value, int type, int pos);
void	token_add_back(t_token **lst, t_token *to_add);
t_token	*last_token(t_token *token);
void	quotes_neutralizer(t_token *lst);

//src/error/error.c
void	error_handler(char *error);

//buiding function
void	print_lst(t_token *token);

#endif
