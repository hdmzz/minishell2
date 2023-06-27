/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:53:06 by hdamitzi          #+#    #+#             */
/*   Updated: 2022/12/12 10:53:08 by hdamitzi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*gnl_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*clean_save(char *save)
{
	char	*new_save;
	char	*ptr;
	int		len;

	ptr = gnl_strchr(save, '\n');
	if (!ptr)
	{
		new_save = NULL;
		return (gnl_free(&save));
	}
	else
		len = (ptr - save) + 1;
	if (!save[len])
		return (gnl_free(&save));
	new_save = gnl_substr(save, len, gnl_strlen(save) - len);
	gnl_free(&save);
	if (!new_save)
		return (NULL);
	return (new_save);
}

char	*new_line(char *save)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = gnl_strchr(save, '\n');
	len = (ptr - save) + 1;
	line = gnl_substr(save, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*read_and_save(int fd, char *save)
{
	int		ret;
	char	*buffer;

	ret = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (gnl_free(&save));
	buffer[0] = '\0';
	while (ret > 0 && !gnl_strchr(buffer, '\n'))
	{
		ret = read (fd, buffer, BUFFER_SIZE);
		if (ret > 0)
		{
			buffer[ret] = '\0';
			save = gnl_strjoin(save, buffer);
		}
	}
	free(buffer);
	if (ret == -1)
		return (gnl_free(&save));
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0)
		return (NULL);
	if ((save && !gnl_strchr(save, '\n')) || !save)
		save = read_and_save (fd, save);
	if (!save)
		return (NULL);
	line = new_line(save);
	if (!line)
		return (gnl_free(&save));
	save = clean_save(save);
	return (line);
}
