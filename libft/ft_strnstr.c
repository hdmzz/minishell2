/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:38:37 by hdamitzi          #+#    #+#             */
/*   Updated: 2022/11/18 10:38:39 by hdamitzi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	needlen;

	if (!needle[0])
		return ((char *)haystack);
	if (!haystack && !len)
		return (NULL);
	i = 0;
	needlen = ft_strlen(needle);
	while (haystack[i] && (i + needlen - 1) < len)
	{
		j = 0;
		while (needle[j] == haystack[i + j] && needle[j])
		{
			if (j == needlen - 1)
				return ((char *)haystack + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
