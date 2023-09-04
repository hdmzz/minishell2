/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vsprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 20:46:03 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/04 13:50:00 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_len(int num)
{
	int	len;

	len = 0;
	if (num < 0)
	{
		len++;
		num = -num;
	}
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

static char	*add_num_to_str(char *str, char *num_str, int digits, int written)
{
	int	i;

	i = digits - 1;
	num_str[digits] = '\0';
	while (i >= 0)
	{
		str[written++] = num_str[i];
		i--;
	}
	return (str);
}

static void	add_formatted_int(char *str, int *written, va_list args, int *i)
{
	int		digits;
	char	*num_str;
	int		num;

	num = va_arg(args, int);
	digits = num_len(num);
	num_str = ft_itoa(num);
	str = add_num_to_str(str, num_str, digits, *written);
	*written += digits;
	*i += 2;
}

// Fonction pour ajouter une chaîne formatée à la chaîne
void	add_formatted_string(char *str, int *written, va_list args, int *i)
{
	const char	*s;

	s = va_arg(args, const char *);
	while (*s != '\0')
	{
		str[*written] = *s;
		(*written)++;
		s++;
	}
	*i += 2;
}

int	ft_vsprintf(char *str, const char *format, ...)
{
	int		written;
	int		i;
	va_list	args;

	va_start(args, format);
	i = 0;
	written = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			if (format[i + 1] == 'd')
				add_formatted_int(str, &written, args, &i);
			else if (format[i + 1] == 's')
				add_formatted_string(str, &written, args, &i);
			else
				str[written++] = format[i++];
		}
		else
			str[written++] = format[i++];
	}
	str[written] = '\0';
	va_end(args);
	return (written);
}
