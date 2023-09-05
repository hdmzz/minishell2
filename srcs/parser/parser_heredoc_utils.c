/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:22:48 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/06 01:31:46 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (tmp[i][0] == '(')
		{
			tmp[i] = ft_free_ptr(tmp[i]);
			tmp[i] = cmd_output;
		}
		i++;
	}
	new_input = recompose_input(tmp);
	return (new_input);
}
