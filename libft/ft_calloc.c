/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:39:44 by hdamitzi          #+#    #+#             */
/*   Updated: 2022/11/18 10:39:50 by hdamitzi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*buff;
	size_t	i;

	i = count * size;
	if (i && i / size != count)
		return (NULL);
	buff = malloc(size * count);
	if (!buff)
		return (NULL);
	ft_bzero(buff, size * count);
	return (buff);
}
