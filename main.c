/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 04:05:03 by yamrire           #+#    #+#             */
/*   Updated: 2022/06/29 06:01:08 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_error(int static_code)
{
	perror("pipex");
	exit(static_code);
}

int	open_files(t_Pipex *cmd, char **av)
{
	cmd->fd_infile = open(av[1], O_RDONLY);
	cmd->fd_outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_infile == -1)
	{
		perror("pipex");
		return (1);
	}
	if (cmd->fd_outfile == -1)
		handle_error(errno);
	return (0);
}

int	main(int ac, char *av[], char **envp)
{
	t_Pipex	cmd;
	int		ret_filefd;

	if (ac != 5)
	{
		ft_printf("ERROR : INCORRECT ARGUMENTS !\n");
		return (0);
	}
	cmd.cmd_options = NULL;
	ret_filefd = open_files(&cmd, av);
	if (pipe(cmd.fd_pip))
		handle_error(errno);
	if (ret_filefd != 1)
		in_process(&cmd, av[2], envp);
	cmd.pid2 = fork();
	if (cmd.pid2 == -1)
		handle_error(errno);
	else if (cmd.pid2 == 0)
		out_process(cmd, av[3], envp);
	else
		parent_process(cmd, ret_filefd);
	return (0);
}
