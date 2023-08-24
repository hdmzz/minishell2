/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 02:51:58 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/08/24 11:08:24 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_mkstemp(char *filename)
{
	int	i;
	int	try_max;
	int	fd;

	i = 0;
	try_max = 0;
	fd = open(filename, O_CREAT | O_EXCL | O_RDWR | O_TRUNC, 0600);
	while (fd == -1 && try_max <= 15)
	{
		while (filename[i] && filename[i] != '0')
			i++;
		if (filename[i] && ft_isalnum(filename[i] + 1))
			filename[i] = filename[i] + 1;
		else
			filename[i] = 'a';
		fd = open(filename, O_CREAT | O_EXCL | O_RDWR | O_TRUNC, 0600);
		try_max++;
	}
	if (try_max == 15)
		return (-1);
	return (fd);
}

void	prep_heredoc(t_cmd *c, char *delim)
{
	static char	tmpfile[] = "tmpfile0";

	c->heredoc = 1;
	c->fd_heredoc = ft_mkstemp(tmpfile);
	if (c->fd_heredoc == -1)
		return (perror("too many temporary files"));
	c->fd_in = open(tmpfile, O_RDONLY, NULL);
	c->heredoc_delim = delim;
	unlink(tmpfile);
}

//quel est le but 
//on recup la commande si << il ya il faut extraire le delim
//creer un fichier temp
//puis ouvrir un fd pour ecrire sur un fichier temp
//stocker ca ds le c->fd-in
//et un autre fd qui pointe vers le meme fichier 

//donc 2 fds a ouvrir un pour l'exec de la fction heredoc
//et un pour l'execution de la commande en elle meme

//indiqer a la commande qu'il y a un heredoc
//cmd->heredoc == 1 alors --:>lancement boucle infini ecriture
//sur premier fd puis close
//et redir sur fdcpy

//puis lors de l'execution la fonction heredoc fer

static int	left_redir(t_cmd *c)
{
	int		i;
	char	**cmd;
	int		split_len;

	i = -1;
	c->heredoc = 0;
	cmd = c->cmd;
	split_len = split_lenght(cmd);
	if (!cmd)
		return (1);
	while (++i < split_len && cmd[i])
	{
		if (cmd[i][0] == '<')
		{
			if (ft_strcmp(cmd[i], "<<") == 0)
				prep_heredoc(c, cmd[i + 1]);
			else
				c->fd_in = open(cmd[i + 1], O_RDONLY, NULL);
			if (c->fd_in == -1)
				return (0);
			cmd[i] = NULL;
			cmd[i + 1] = NULL;
			i++;
		}
	}
	return (1);
}

static int	right_redir(t_cmd *c)
{
	int		i;
	int		fd;
	int		oflag;
	char	**cmd;
	int		split_len;

	i = 0;
	oflag = O_WRONLY | O_CREAT | O_TRUNC;
	cmd = c->cmd;
	split_len = split_lenght(c->cmd);
	while (i < split_len)
	{
		if (cmd[i][0] == '>' && ft_strlen(cmd[i]) <= 2)
		{
			if (!ft_strcmp(cmd[i], ">>"))
				oflag = O_WRONLY | O_APPEND | O_CREAT;
			fd = open(cmd[i + 1], oflag, 0644);
			if (fd == -1)
				return (-1);
			c->fd_out = fd;
			cmd[i] = NULL;
			cmd[i + 1] = NULL;
			i++;
		}
		i++;
	}
	return (1);
}

int	prepare_io(t_cmd *c)
{
	t_cmd	*tmp;

	tmp = c;
	while (tmp)
	{
		left_redir(tmp);
		right_redir(tmp);
		tmp = tmp->next;
	}
	return (1);
}
