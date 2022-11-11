/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:48:25 by yamrire           #+#    #+#             */
/*   Updated: 2022/11/11 10:55:16 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	cmpstr(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	n;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	n = 0;
	if (len1 != len2)
		return (0);
	while (n < len1)
	{
		if (s1[n] != s2[n])
			return (0);
		n++;
	}
	return (1);
}

void	handle_error(int static_code)
{
	perror("pipex");
	exit(static_code);
}

void	free_double(char **pointer)
{
	int	i;

	i = 0;
	while (pointer[i])
	{
		free(pointer[i]);
		i++;
	}
	free(pointer);
	pointer = NULL;
}

int	open_heredoc(t_pipex *cmd, char *av)
{
	cmd->fd_infile = open("/tmp/.here_doc",
			O_APPEND | O_CREAT | O_RDWR | O_TRUNC, 0644);
	cmd->fd_outfile = open(av, O_APPEND | O_CREAT | O_RDWR, 0644);
	if (cmd->fd_infile == -1)
	{
		perror("pipex");
		return (1);
	}
	if (cmd->fd_outfile == -1)
		handle_error(errno);
	return (0);
}

int	open_files(t_pipex *cmd, int ac, char **av)
{
	cmd->fd_infile = open(av[1], O_RDONLY);
	cmd->fd_outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_infile == -1)
	{
		perror("pipex");
		return (1);
	}
	if (cmd->fd_outfile == -1)
		handle_error(errno);
	return (0);
}
