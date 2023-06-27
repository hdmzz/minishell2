/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:22:32 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/15 13:24:35 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(int i, char *str, char *charset)
{
	int	j;

	j = 0;
	while (charset[j])
	{
		if (str[i] == charset[j])
			return (0);
		j++;
	}
	return (1);
}

static char	**countword(char *str, char *charset)
{
	int		i;
	int		count;
	char	**tab;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && check(i, str, charset) == 0)
			i++;
		if (str[i])
			count++;
		while (str[i] && check(i, str, charset) == 1)
			i++;
	}
	tab = (char **)malloc(sizeof(char *) * count + 1);
	if (!tab)
		return (NULL);
	tab[count] = NULL;
	return (tab);
}

static char	**countchar(char *str, char *charset, char **tab)
{
	int	i;
	int	k;
	int	count;

	count = 0;
	k = -1;
	i = 0;
	while (str[i])
	{
		while (str[i] && check(i, str, charset) == 0)
			i++;
		while (str[i] && check(i, str, charset) == 1)
		{
			count++;
			i++;
		}
		if (count != 0)
		{
			tab[++k] = (char *)malloc(sizeof(char) * count + 1);
			if (!tab[k])
				return (NULL);
			count = 0;
		}
	}
	return (tab);
}

static char	**fill(char *str, char *charset, char **tab)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	k = 0;
	while (str[i])
	{
		j = 0;
		while (str[i] && check(i, str, charset) == 0)
			i++;
		while (str[i] && check(i, str, charset) == 1)
		{
			tab[k][j] = str[i];
			i++;
			j++;
		}
		if (j != 0)
			tab[k][j] = '\0';
		k++;
	}
	return (tab);
}

char	**ft_split_charset(char *str, char *charset)
{
	char	**tab;

	tab = countword(str, charset);
	tab = countchar(str, charset, tab);
	return (fill(str, charset, tab));
}
