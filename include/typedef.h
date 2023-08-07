#ifndef TYPEDEF_H
# define TYPEDEF_H

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
	int		nb_cmds;//nb pipes + 1
	int		nb_pipes;
	int		output_backup;
	int		input_backup;
	int		**pipes_fd;
	t_io	*io;
	pid_t	*pids;
}			t_shell;

#endif
