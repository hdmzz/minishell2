/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:24:03 by hdamitzi          #+#    #+#             */
/*   Updated: 2022/11/18 11:24:06 by hdamitzi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new;
	size_t	s_len;
	size_t	start;

	if (!s || !f)
		return (NULL);
	s_len = ft_strlen(s);
	new = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!new)
		return (NULL);
	start = 0;
	while (start < s_len)
	{
		new[start] = f(start, s[start]);
		start++;
	}
	new[start] = '\0';
	return (new);
}
