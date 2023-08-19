#ifndef TYPEDEF_H
# define TYPEDEF_H

# include <stdio.h>
# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdbool.h>

extern int	g_last_exit_code;
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
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_cmd
{
	char			**cmd;
	int				nb_of_cmd;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	int				fd_in;
	int				fd_out;
	int				output_backup;
	int				input_backup;
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
	int		nb_cmds;//nb pipes + 1
	int		output_backup;
	int		input_backup;
	t_io	*io;
	int		**pipes_fd;
	pid_t	*pids;
	int		nb_pipes;
}			t_shell;

#endif
