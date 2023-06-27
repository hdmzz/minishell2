/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:05:36 by hdamitzi          #+#    #+#             */
/*   Updated: 2022/12/12 10:05:38 by hdamitzi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putc(char c, int *total)
{
	*total += write(1, &c, 1);
}

void	ft_puts(char *str, int *total)
{
	if (!str)
		ft_puts("(null)", total);
	else
	{
		while (*str != '\0')
		{
			ft_putc(*str, total);
			str++;
		}
	}
}
