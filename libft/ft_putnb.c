/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:05:50 by hdamitzi          #+#    #+#             */
/*   Updated: 2022/12/12 10:05:52 by hdamitzi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	ft_printf_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putnb_base(unsigned long long nb, char *base, int *total)
{
	if (nb >= ft_printf_strlen(base))
		ft_putnb_base(nb / ft_printf_strlen(base), base, total);
	ft_putc(base[nb % ft_printf_strlen(base)], total);
}

void	ft_putnb(unsigned long long nl, int *total)
{
	long long	num;

	num = nl;
	if (num < 0)
	{
		ft_putc('-', total);
		num = -num;
	}
	ft_putnb_base(num, "0123456789", total);
}

void	ft_put_ptr(void *ptr, int *total)
{
	unsigned long long	addr;

	addr = (unsigned long long)ptr;
	ft_puts("0x", total);
	ft_putnb_base(addr, "0123456789abcdef", total);
}
