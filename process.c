/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 06:10:02 by yamrire           #+#    #+#             */
/*   Updated: 2022/06/26 02:03:34 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	in_process(t_Pipex cmd, char *av, char **envp)
{
	if (close (cmd.fd_pip[0]) == -1)
		handle_error("close()");
	cmd.cmd_options = get_cmd_options(av, envp);
	if (dup2(cmd.fd_infile, STDIN_FILENO) == -1)
		handle_error("dup2()");
	if (dup2(cmd.fd_pip[1], STDOUT_FILENO) == -1)
		handle_error("dup2()");
	if (close(cmd.fd_pip[1]) == -1)
		handle_error("close()");
	if (execve(cmd.cmd_options[0], cmd.cmd_options, envp) == -1)
		handle_error("execve()");
}

void	out_process(t_Pipex cmd, char *av, char **envp)
{
	if (close (cmd.fd_pip[1]) == -1)
		handle_error("close()");
	cmd.cmd_options = get_cmd_options(av, envp);
	if (dup2(cmd.fd_outfile, STDOUT_FILENO) == -1)
		handle_error("dup2()");
	if (dup2(cmd.fd_pip[0], STDIN_FILENO))
		handle_error("dup2()");
	if (close(cmd.fd_pip[0]) == -1)
		handle_error("close()");
	if (execve(cmd.cmd_options[0], cmd.cmd_options, envp) == -1)
		handle_error("execve()");
}

void	parent_process(t_Pipex cmd)
{
	if (close(cmd.fd_pip[0]) == -1)
		handle_error("close()");
	if (close(cmd.fd_pip[1]) == -1)
		handle_error("close()");
	while (wait(0) == -1)
		;
	if (close(cmd.fd_infile) == -1)
		handle_error("close()");
	if (close(cmd.fd_outfile) == -1)
		handle_error("close()");
	exit(0);
}
