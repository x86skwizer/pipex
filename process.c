/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 06:10:02 by yamrire           #+#    #+#             */
/*   Updated: 2022/06/28 01:25:02 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	in_process(t_Pipex cmd, char *av, char **envp)
{
	cmd.cmd_options = get_cmd_options(av, envp);
	if (!cmd.cmd_options) {
		ft_printf("pipex: command not found: %s\n", av);
		return;
	}
	cmd.pid1 = fork();
	if (cmd.pid1 == -1)
		handle_error(errno);
	else if (cmd.pid1 == 0)
	{
		if (close (cmd.fd_pip[0]) == -1)
			handle_error(errno);
		if (dup2(cmd.fd_infile, STDIN_FILENO) == -1)
			handle_error(errno);
		if (dup2(cmd.fd_pip[1], STDOUT_FILENO) == -1)
			handle_error(errno);
		if (close(cmd.fd_pip[1]) == -1)
			handle_error(errno);
		if (close(cmd.fd_infile) == -1)
			handle_error(errno);
		if (execve(cmd.cmd_options[0], cmd.cmd_options, envp) == -1)
			handle_error(errno);
	}
}

void	out_process(t_Pipex cmd, char *av, char **envp)
{
	if (close (cmd.fd_pip[1]) == -1)
		handle_error(errno);
	cmd.cmd_options = get_cmd_options(av, envp);
	if (!cmd.cmd_options) {
		ft_printf("pipex: command not found: %s\n", av);
		return;
	}
	if (dup2(cmd.fd_outfile, STDOUT_FILENO) == -1)
		handle_error(errno);
	if (dup2(cmd.fd_pip[0], STDIN_FILENO))
		handle_error(errno);
	if (close(cmd.fd_pip[0]) == -1)
		handle_error(errno);
	if (close(cmd.fd_outfile) == -1)
		handle_error(errno);
	if (execve(cmd.cmd_options[0], cmd.cmd_options, envp) == -1)
		handle_error(errno);
}

void	parent_process(t_Pipex cmd, int ret)
{
	if (close(cmd.fd_pip[0]) == -1)
		handle_error(errno);
	if (close(cmd.fd_pip[1]) == -1)
		handle_error(errno);
	if (ret != 1) {
		if (close(cmd.fd_infile) == -1)
			handle_error(errno);
	}
	if (close(cmd.fd_outfile) == -1)
		handle_error(errno);
	waitpid(cmd.pid1, NULL, 0);
	waitpid(cmd.pid2, NULL, 0);
	
	// while (wait(0) == -1)
	// 	;
	exit(0);
}
