#include "../../include/minishell.h"



static int	delim_in_quotes(t_token *lst)
{
	int	delim_in_quotes;

	delim_in_quotes = 0;
	while (lst->type == white_space)
		lst = lst->next;
	if (lst->type == double_quote)
	{
		while (lst->type & 608)
			lst = lst->next;
		if (lst->type != double_quote)
			delim_in_quotes = 1;
	}
	return (delim_in_quotes);
}

int	heredoc_first_analyzer(t_shell *g_shell)
{
	t_token	*lst;

	lst = g_shell->list_token;
	while (lst)
	{
		if (lst->type == double_redir_left)
		{
			g_shell->io->heredoc = 1;
			if (delim_in_quotes(lst))
				g_shell->io->delim_in_quotes = 1;
		}
		lst = lst->next;
	}
	return (1);
}

int	input_into_parenthesis(char *input, int *i)
{
	int	y;

	y = 0;
	*i += 1;
	if (input[*i] == '(')
	{
		*i += 1;
		y = *i;
		while (input[y] && input[y] != ')')
			y++;
		if (!input[y])
			return (0);
		if (input[y] == ')')
			return (y);
	}
	return (0);
}


/* 
	this function takes the original input str and substitute the heredoc cmd with the value
	so to do that we
 */
char	*substitute_input_wth_output(char *input, char *cmd_output)
{
	char	**tab;
	char	**tmp;
	char	*new_input;
	int		total_len;
	int		i;

	total_len = 0;
	tab = ft_split_charset(input, "$");
	tmp = tab;
	if (!tab)
	{
		perror("Split cmd output");
		return (NULL);
	}
	i = 0;
	while (tmp[i])
	{
		if (tmp[i][0] == '(')//on a une commande a executer etc
			tmp[i] = cmd_output;
		i++;
	}
	while (i--)
		total_len += ft_strlen(tmp[i]);
	i++;
	new_input = ft_calloc(total_len + 1, sizeof(char));
	if (!new_input)
		return (NULL);
	new_input[0] = '\0';//peut etre pas besoin de faire ca puisque tout est init a zero avec calloc
	while (tmp[i])
	{
		ft_strlcat(new_input, tmp[i], total_len + 1);
		i++;
	}
	ft_free_split(tab);
	free(input);
	return (new_input);
}

/* 
	for each input of the heredoc
 */
char	*heredoc_expanser(char *input, t_io *std_io)
{
	char	*inp;
	char	*imbrecated_cmd;
	char	*cmd_output;
	int		i;
	int		y;

	i = 0;
	y = 0;
	inp = input;
	if (std_io->delim_in_quotes)
		return (inp);
	while (inp[i])
	{
		if (inp[i] == '$')
		{
			y = input_into_parenthesis(input, &i);
			if (y > i)
			{
				imbrecated_cmd = ft_substr(input, i, y - i);
				cmd_output = pipe_heredoc(imbrecated_cmd);
				inp = substitute_input_wth_output(input, cmd_output);
			}
		}
		i++;
	}
	return (inp);
}
