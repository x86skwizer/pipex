/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 06:10:02 by yamrire           #+#    #+#             */
/*   Updated: 2022/06/26 00:45:21 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	in_process(Pipex cmd, char *av, char **envp)
{
	if (close (cmd.fd_pip[0]) == -1)
		handle_error();
	cmd.cmd_options = get_cmd_options(av, envp);
	if (dup2(cmd.fd_infile, STDIN_FILENO) == -1)
		handle_error();
	if (dup2(cmd.fd_pip[1], STDOUT_FILENO)== -1)
		handle_error();
	if (close(cmd.fd_pip[1]) == -1)
		handle_error();
	if (execve(cmd.cmd_options[0], cmd.cmd_options, envp) == -1)
		handle_error();
}

void	out_process(Pipex cmd, char *av, char **envp)
{
	if (close (cmd.fd_pip[1]) == -1)
		handle_error();
	cmd.cmd_options = get_cmd_options(av, envp);
	if (dup2(cmd.fd_outfile, STDOUT_FILENO) == -1)
		handle_error();
	if (dup2(cmd.fd_pip[0], STDIN_FILENO))
		handle_error();
	if (close(cmd.fd_pip[0]) == -1)
		handle_error();
	if (execve(cmd.cmd_options[0], cmd.cmd_options, envp) == -1)
		handle_error();
}

void	parent_process(Pipex cmd)
{
	if (close(cmd.fd_pip[0]) == -1)
		handle_error();
	if (close(cmd.fd_pip[1]) == -1)
		handle_error();
	while (wait(0) == -1);
	if (close(cmd.fd_infile) == -1)
		handle_error();
	if (close(cmd.fd_outfile) == -1)
		handle_error();
	exit(0);
}