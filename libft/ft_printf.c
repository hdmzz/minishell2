/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:41:41 by hdamitzi          #+#    #+#             */
/*   Updated: 2022/11/30 11:41:44 by hdamitzi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dispatch(va_list params, const char *format, int i, int *total)
{
	if (format[i] == 's')
		ft_puts(va_arg(params, char *), total);
	else if (format[i] == 'c')
		ft_putc(va_arg(params, int), total);
	else if (format[i] == 'x')
		ft_putnb_base(va_arg(params, unsigned int),
			"0123456789abcdef", total);
	else if (format[i] == 'X')
		ft_putnb_base(va_arg(params, unsigned int),
			"0123456789ABCDEF", total);
	else if (format[i] == 'p')
		ft_put_ptr(va_arg(params, void *), total);
	else if (format[i] == 'd' || format[i] == 'i')
		ft_putnb(va_arg(params, int), total);
	else if (format[i] == 'u')
		ft_putnb(va_arg(params, unsigned int), total);
	else if (format[i] == '%')
		ft_putc('%', total);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		total;

	i = 0;
	total = 0;
	if (write(1, 0, 0) == -1)
		return (-1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			ft_dispatch(args, format, i + 1, &total);
			i++;
		}
		else if (write(1, &format[i], 1))
			total += 1;
		i++;
	}
	va_end(args);
	return (total);
}
