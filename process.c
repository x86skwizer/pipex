/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 06:10:02 by yamrire           #+#    #+#             */
/*   Updated: 2022/06/26 00:02:20 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	in_process(Pipex cmd, char *av, char **envp)
{
	close (cmd.fd_pip[0]);
	cmd.cmd_options = get_cmd_options(av, envp);
	dup2(cmd.fd_infile, STDIN_FILENO);
	dup2(cmd.fd_pip[1], STDOUT_FILENO);
	close(cmd.fd_pip[1]);
	execve(cmd.cmd_options[0], cmd.cmd_options, envp);
}

void	out_process(Pipex cmd, char *av, char **envp)
{
	close (cmd.fd_pip[1]);
	cmd.cmd_options = get_cmd_options(av, envp);
	dup2(cmd.fd_outfile, STDOUT_FILENO);
	dup2(cmd.fd_pip[0], STDIN_FILENO);
	close(cmd.fd_pip[0]);
	execve(cmd.cmd_options[0], cmd.cmd_options, envp);
}

void	parent_process(Pipex cmd)
{
	close(cmd.fd_pip[0]);
	close(cmd.fd_pip[1]);
	while (wait(0) == -1);
	close(cmd.fd_infile);
	close(cmd.fd_outfile);
	exit(0);
}