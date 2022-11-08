/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:26:43 by yamrire           #+#    #+#             */
/*   Updated: 2022/03/15 12:48:52 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	new_line_index(char *str)
{
	int	index;

	index = 0;
	while (str[index] && str[index] != '\n')
		index++;
	return (index);
}

char	*analyse_line(char **stash)
{
	char	*line;
	char	*tmp;
	int		index;

	if (!*stash || !(*stash)[0])
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	index = new_line_index(*stash);
	if ((*stash)[index] == '\n')
	{
		line = ft_substr(*stash, 0, index + 1);
		tmp = ft_strdup((*stash) + (index + 1));
		free(*stash);
		*stash = tmp;
		return (line);
	}
	line = ft_strdup(*stash);
	free(*stash);
	*stash = NULL;
	return (line);
}

void	form_line(int fd, char **stash, char *buff, ssize_t rd)
{
	char	*tmp;

	while (rd > 0)
	{
		tmp = ft_strjoin(*stash, buff);
		free(*stash);
		*stash = tmp;
		if (ft_strchr(*stash, '\n') != NULL)
			break ;
		rd = read(fd, buff, BUFFER_SIZE);
		buff[rd] = '\0';
	}
	free(buff);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buff;
	char		*line;
	ssize_t		rd;

	buff = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	rd = read(fd, buff, BUFFER_SIZE);
	if (rd == -1)
	{
		free (buff);
		return (NULL);
	}
	buff[rd] = '\0';
	if (!stash)
		stash = ft_strdup("");
	form_line(fd, &stash, buff, rd);
	line = analyse_line(&stash);
	return (line);
}
