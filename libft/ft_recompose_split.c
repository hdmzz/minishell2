/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recompose_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 22:30:08 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/04 13:54:19 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	split_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

static char	*recompose_strings(char **strs, int num_strs, char sep, int i)
{
	int		total_length;
	char	*res;
	int		pos;

	total_length = 0;
	while (++i < num_strs)
		total_length += ft_strlen(strs[i]);
	total_length += num_strs - 1;
	res = (char *)malloc(total_length + 1);
	if (res == NULL)
		return (NULL);
	pos = 0;
	while (++i < num_strs)
	{
		ft_strlcpy(res + pos, strs[i], total_length + 1);
		pos += ft_strlen(strs[i]);
		if (i != num_strs -1)
		{
			ft_strlcpy(res + pos, &sep, total_length + 1);
			pos += 1;
		}
	}
	return (res);
}

char	*ft_recompose_split(char **strs, char sep)
{
	int		num_strs;
	char	*recomposed;

	num_strs = split_size(strs);
	recomposed = recompose_strings(strs, num_strs, sep, -1);
	return (recomposed);
}
