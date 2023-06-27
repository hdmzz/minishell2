/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:24:28 by hdamitzi          #+#    #+#             */
/*   Updated: 2022/11/14 14:24:31 by hdamitzi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **res, int i)
{
	int	j;

	j = 0;
	while (j < i && res[j] != 0)
		free(res[j++]);
	free(res);
	return (NULL);
}

static int	ft_wordlen(const char	*s, char sep)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != sep)
		i++;
	return (i);
}

static int	ft_countwords(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		i = ft_wordlen(s, c);
		if (i != 0)
			count++;
		s += i;
	}
	return (count);
}

static char	*ft_wordup(const char	*s, int n)
{
	char	*buff;

	buff = malloc(sizeof(char) * (n + 1));
	if (!buff)
		return (NULL);
	buff[n] = '\0';
	while (n--)
		buff[n] = s[n];
	return (buff);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		wordcount;
	int		i;
	int		j;

	wordcount = ft_countwords(s, c);
	split = malloc(sizeof(char *) * (wordcount + 1));
	if (!split)
		return (NULL);
	j = 0;
	while (wordcount--)
	{
		while (*s && *s == c)
			s++;
		i = ft_wordlen(s, c);
		if (i)
			split[j] = ft_wordup(s, i);
		if (!split[j])
			return (ft_free(split, j));
		s += i;
		j++;
	}
	split[j] = NULL;
	return (split);
}
