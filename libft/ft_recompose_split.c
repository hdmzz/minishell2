/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recompose_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 22:30:08 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/15 23:27:50 by hdamitzi         ###   ########.fr       */
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

static char	*recompose_strings(char** strs, int num_strs, char sep)
{
	int		total_length;
	int		i;
	char	*res;
	int		pos;

	total_length = 0;
	i = -1;
	while (++i < num_strs)
		total_length += ft_strlen(strs[i]);
	total_length += num_strs - 1;
	// Allouer de la mémoire pour la chaîne recomposée
	res = (char*)malloc(total_length + 1);  // +1 pour le caractère null de fin de chaîne
	if (res == NULL)
		exit(EXIT_FAILURE);
	// Copier les chaînes individuelles dans la chaîne recomposée
	pos = 0;
	i = -1;
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
	recomposed = recompose_strings(strs, num_strs, sep);
	return (recomposed);
}
