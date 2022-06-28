/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 04:05:03 by yamrire           #+#    #+#             */
/*   Updated: 2022/06/28 00:58:09 by yamrire          ###   ########.fr       */
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
	cmd->fd_outfile = open(av[4], O_WRONLY | O_CREAT, 0666);
	if (cmd->fd_infile == -1) {
		perror("pipex");
		return 1;	
	}
	if (cmd->fd_outfile == -1)
		handle_error(errno);
	return 0;
}

int	main(int ac, char *av[], char **envp)
{
	t_Pipex	cmd;

	if (ac != 5)
		ft_printf("ERROR : INCORRECT ARGUMENTS !\n");
	cmd.cmd_options = NULL;
	int ret = open_files(&cmd, av);
	
	if (pipe(cmd.fd_pip))
		handle_error(errno);
	// run first command
	if (ret != 1) {
		in_process(cmd, av[2], envp);
	}
	// run second command
	cmd.pid2 = fork();
	if (cmd.pid2 == -1)
		handle_error(errno);
	else if (cmd.pid2 == 0)
		out_process(cmd, av[3], envp);
	else
		parent_process(cmd, ret);
	return (0);
}
