/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 04:05:03 by yamrire           #+#    #+#             */
/*   Updated: 2022/06/26 01:30:42 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_error(void)
{
	perror(strerror(errno));
	exit(errno);
}

void	open_files(t_Pipex *cmd, char **av)
{
	cmd->fd_infile = open(av[1], O_RDONLY);
	cmd->fd_outfile = open(av[4], O_WRONLY | O_CREAT, 0666);
	if (cmd->fd_infile == -1 || cmd->fd_outfile == -1)
		handle_error();
}

int	main(int ac, char *av[], char **envp)
{
	t_Pipex	cmd;
	pid_t	pid1;
	pid_t	pid2;

	if (ac != 5)
		ft_printf("ERROR : INCORRECT ARGUMENTS !\n");
	cmd.cmd_options = NULL;
	open_files(&cmd, av);
	if (pipe(cmd.fd_pip))
		handle_error();
	pid1 = fork();
	if (pid1 == -1)
		handle_error();
	else if (pid1 == 0)
		in_process(cmd, av[2], envp);
	pid2 = fork();
	if (pid2 == -1)
		handle_error();
	else if (pid2 == 0)
		out_process(cmd, av[3], envp);
	else
		parent_process(cmd);
	return (0);
}
