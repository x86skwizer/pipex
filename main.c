/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 04:05:03 by yamrire           #+#    #+#             */
/*   Updated: 2022/06/26 00:06:58 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	main(int ac, char *av[], char **envp)
{
	Pipex	cmd;
	pid_t	pid1;
	pid_t	pid2;

	if (ac == 5)
	{
		cmd.fd_infile = open(av[1], O_RDONLY);
		cmd.fd_outfile = open(av[4], O_WRONLY | O_CREAT, 0666);
		pipe(cmd.fd_pip);
		pid1 = fork();
		if (pid1 == 0)
		{
			in_process(cmd, av[2], envp);
		}
		else
		{
			pid2 = fork();
			if (pid2 == 0)
			{
				out_process(cmd, av[3], envp);
			}
			else
			{
				parent_process(cmd);
			}
		}
	}
	else
		ft_printf("ERROR : Wrong parameters !\n");

		
	return (0);
}