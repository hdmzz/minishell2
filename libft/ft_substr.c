/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:38:00 by hdamitzi          #+#    #+#             */
/*   Updated: 2022/11/18 10:38:03 by hdamitzi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	new_len;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		new = ft_calloc(1, sizeof(char));
		if (!new)
			return (NULL);
	}
	else
	{
		new_len = ft_strlen(s + start);
		if (!(new_len < len))
			new_len = len;
		new = (char *)malloc(sizeof(char) * (new_len + 1));
		if (!new)
			return (NULL);
		new[new_len] = '\0';
		while (new_len--)
			new[new_len] = s[start + new_len];
	}
	return (new);
}
