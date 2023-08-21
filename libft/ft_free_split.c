/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:16:34 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/19 22:10:26 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != NULL)
	{
		if (tab[i] != NULL)
			ft_free_ptr(tab[i]);
		i++;
	}
	ft_free_ptr(tab);
}
