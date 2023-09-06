/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:13:46 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/06 12:21:15 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include <stdio.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <errno.h>
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

extern int	g_last_exit_code;

enum e_error{
	COMMAND_NOT_FOUND = 127,
	BAD_COMMAND_USAGE = 128,
	FILE_NOT_FOUND = 1,
	INSUFFICIENT_PERMISSIONS = 126,
	BAD_ARGUMENT_COUNT = 2,
	BAD_REDIRECTION = 3,
	COMMAND_SUBSTITUTION_FAILED = 4,
	UNDEFINED_VARIABLE = 5,
	BAD_QUOTE_USAGE = 6,
	UNEXPECTED_SYNTAX_ERROR = 7,
	BAD_OPERATOR_USAGE = 8
};

enum e_type
{
	new_line,
	pipeline,
	simple_redir_left = 2,
	simple_redir_right = 4,
	double_redir_left = 8,
	double_redir_right = 16,
	white_space = 32,
	single_quote = 64,
	double_quote = 128,
	dollar = 256,
	literal = 512,
	start_type
};

enum e_redir
{
	less,
	larger,
	d_less,
	d_larger,
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
	int				hd_delim_into_quotes;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
	struct s_shell	*g_shell;
}				t_token;

typedef struct s_cmd
{
	char			**cmd;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	char			*full_cmd_path;
	char			*heredoc_delim;
	int				idx_cmd;
	int				nb_of_cmd;
	int				pipes_fd[2];
	int				fd_in;
	int				fd_out;
	int				output_backup;
	int				input_backup;
	int				heredoc;
	int				fd_heredoc;
	int				hd_delim_into_quotes;
	struct s_shell	*g_shell;
}				t_cmd;

typedef struct s_io
{
	int	heredoc;
	int	delim_in_quotes;
	int	var_expanser;
}			t_io;

typedef struct s_shell
{
	char	*start_buff;
	char	*full_cmd_path;
	char	**splitted_cmd;
	char	**split_env;
	t_token	*list_token;
	t_token	*start_token;
	t_cmd	*cmds;
	t_cmd	*start_cmd;
	int		nb_cmds;
	int		output_backup;
	t_io	*io;
	int		input_backup;
	int		**pipes_fd;
	pid_t	*pids;
	int		nb_pipes;
}			t_shell;

#endif
