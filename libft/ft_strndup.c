/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:54:28 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/27 15:59:54 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t n)
{
	size_t	length;

	length = ft_strnlen(str, n);
	char *duplicate = malloc(length + 1);
	if (duplicate != NULL)
	{
		ft_memcpy(duplicate, str, length);
		duplicate[length] = '\0';
	}
	return (duplicate);
}
