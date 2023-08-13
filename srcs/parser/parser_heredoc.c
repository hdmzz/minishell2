#include "../../include/minishell.h"

static int	delim_in_quotes(t_token *lst)
{
	int	delim_in_quotes;

	delim_in_quotes = 0;
	while (lst->type == white_space || lst->type == double_redir_left)
		lst = lst->next;
	if (lst->type == double_quote)
	{
		lst = lst->next;
		while (lst && lst->type != double_quote)
			lst = lst->next;
		if (lst && lst->type == double_quote)
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
	need a function that recompose the input from the char ** 
	so this function calculates the total lenght of the final char *
 */
char	*recompose_input(char **tab)
{
	char	*new_input;
	int		total_len;
	int		tab_len;
	int		i;

	total_len = 0;
	i = -1;
	while (tab[++i])
		total_len += ft_strlen(tab[i]);
	tab_len = i;
	total_len += i - 1;
	new_input = ft_calloc(total_len + 1, sizeof(char));
	if (!new_input)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		ft_strlcat(new_input, tab[i], total_len + 1);
		if (i < tab_len - 1)
			ft_strlcat(new_input, " ", total_len + 1);
		i++;
	}
	ft_free_split(tab);
	return (new_input);
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
	int		i;

	tab = ft_split(input, '$');
	tmp = tab;
	if (!tab || !cmd_output)
		return (perror("Error substitute_input_wth_output"), NULL);
	i = 0;
	while (tmp[i])
	{
		if (tmp[i][0] == '(')//on a une commande a executer etc
			tmp[i] = cmd_output;
		i++;
	}
	new_input = recompose_input(tmp);
	return (new_input);
}

char	*heredoc_var_xpanser(char *input)
{
	char	**tab;
	char	*temp;
	char	*buff;
	int		i;

	i = 0;
	tab = ft_split(input, 32);
	while (tab[i])
	{
		if (tab[i][0] == '$')
		{
			buff = tab[i];
			temp = var_xpanser(buff);
			ft_free_split(tab);
			return (temp);
		}
		i++;
	}
	return (NULL);
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
	while (inp[i] != '\0')//on est encore sur la str original
	{
		if (inp[i] == '$')// si je suis sur un $ signe soit jexecute une commande soit j'expanse une variable
		{
			y = input_into_parenthesis(input, &i);
			if (y > i)
			{
				imbrecated_cmd = ft_substr(input, i, y - i);
				cmd_output = exec_imbricated_cmd(imbrecated_cmd, 0);
				inp = substitute_input_wth_output(input, cmd_output);//free input original ici
			}
			else
			{
				std_io->var_expanser = 1;
				inp = heredoc_var_xpanser(input);
			}
			free(input);
		}
		i++;
	}
	return (inp);
}
