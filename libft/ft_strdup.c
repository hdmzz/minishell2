/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:39:14 by hdamitzi          #+#    #+#             */
/*   Updated: 2022/11/18 10:39:18 by hdamitzi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*newstr;
	char	*buff;
	int		slen;

	slen = ft_strlen(s1);
	newstr = (char *)malloc(sizeof(char) * (slen + 1));
	if (!newstr)
		return (NULL);
	buff = (char *)s1;
	newstr[slen] = 0;
	while (slen--)
		newstr[slen] = buff[slen];
	return (newstr);
}
