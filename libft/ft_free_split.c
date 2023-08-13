/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:16:34 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/13 16:41:32 by hdamitzi         ###   ########.fr       */
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
			free(tab[i]);
		i++;
	}
	free(tab);
}
