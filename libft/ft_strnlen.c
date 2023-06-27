/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:57:18 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/27 15:58:32 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

size_t	ft_strnlen(const char *str, size_t n)
{
	size_t length = 0;

	while (length < n && str[length] != '\0')
		length++;
	return length;
}
