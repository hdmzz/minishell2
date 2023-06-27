/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:53:21 by hdamitzi          #+#    #+#             */
/*   Updated: 2022/11/14 14:53:25 by hdamitzi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		to_find;
	unsigned char const	*str;
	size_t				i;

	to_find = (unsigned char)c;
	str = (unsigned char const *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == to_find)
			return ((void *)(str + i));
		i++;
	}
	return (NULL);
}
