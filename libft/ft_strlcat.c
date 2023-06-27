/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:27:47 by hdamitzi          #+#    #+#             */
/*   Updated: 2022/11/11 15:27:54 by hdamitzi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	i;

	if (!dst && !dstsize)
		return (0);
	dlen = ft_strlen(dst);
	i = 0;
	if (dstsize <= dlen)
		return (ft_strlen(src) + dstsize);
	while (src[i] && (dlen + i) < (dstsize - 1))
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = 0;
	return (ft_strlen(src) + dlen);
}
