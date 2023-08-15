/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vsprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 20:46:03 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/15 11:51:54 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_len(int num)
{
	int len;

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

//				str=str ou ecrire,   format par ex"%d=%d", args=les truc a mettre a la place des %d ou s 
int	ft_vsprintf(char *str, const char *format, ...) {
	int		written = 0;  // Pour suivre le nombre de caractères écrits dans la chaîne str
	int		i = 0;		// Pour parcourir la chaîne de format
	int		digits;
	char	*num_str;
	int		num;
	va_list	args;

	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			if (format[i + 1] == 'd')
			{
				// Conversion d'un entier en chaîne de caractères
				num = va_arg(args, int);
				digits = num_len(num);
				num_str = ft_itoa(num);
				// Ajouter numStr à la chaîne str
				str = add_num_to_str(str, num_str, digits, written);
				i += 2;
			}
			else if (format[i + 1] == 's')
			{
				char *s = va_arg(args, char *);

				// Copier la chaîne s dans la chaîne str
				while (*s != '\0') {
					str[written++] = *s++;
				}
				i += 2;
			}
			else
				str[written++] = format[i++];
		}
		else
		{
			// Copier les caractères normaux
			str[written++] = format[i++];
		}
	}
	// Ajouter le caractère de fin de chaîne
	str[written] = '\0';
	return (written);
}
