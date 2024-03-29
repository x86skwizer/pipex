/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 07:54:53 by yamrire           #+#    #+#             */
/*   Updated: 2022/11/21 14:43:46 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**pre_in_process(t_pipex *cmd, char *cmd_av)
{
	char	**cmd_options;

	cmd_options = get_cmd_options(cmd, cmd_av);
	if (!cmd_options)
	{
		ft_printf("pipex: %s:command not found\n", cmd_av);
		return (NULL);
	}
	return (cmd_options);
}

void	in_process(t_pipex *cmd, char *cmd_av, pid_t *pid, char **envp)
{
	cmd->cmd_options = pre_in_process(cmd, cmd_av);
	if (!cmd->cmd_options)
		return ;
	*pid = fork();
	if (*pid == -1)
		handle_error(errno);
	else if (*pid == 0)
	{
		if (close(cmd->fd_pip[0]) == -1)
			handle_error(errno);
		if (dup2(cmd->fd_infile, 0) == -1)
			handle_error(errno);
		if (dup2(cmd->fd_pip[1], 1) == -1)
			handle_error(errno);
		if (close(cmd->fd_pip[1]) == -1)
			handle_error(errno);
		if (close(cmd->fd_infile) == -1)
			handle_error(errno);
		if (execve(cmd->cmd_options[0], cmd->cmd_options, envp) == -1)
			handle_error(errno);
	}
	else
		free_double(cmd->cmd_options);
}

void	mid_process(t_pipex *cmd, char **envp)
{
	if (close(cmd->fd_pip[0]) == -1)
		handle_error(errno);
	if (dup2(cmd->fd_pip[1], 1) == -1)
		handle_error(errno);
	if (dup2(cmd->fd_tmp, 0) == -1)
		handle_error(errno);
	if (close(cmd->fd_tmp) == -1)
		handle_error(errno);
	if (close(cmd->fd_pip[1]) == -1)
		handle_error(errno);
	if (execve(cmd->cmd_options[0], cmd->cmd_options, envp) == -1)
		handle_error(errno);
}

void	out_process(t_pipex *cmd, char **envp)
{	
	if (dup2(cmd->fd_outfile, 1) == -1)
		handle_error(errno);
	if (dup2(cmd->fd_tmp, 0) == -1)
		handle_error(errno);
	if (close(cmd->fd_tmp) == -1)
		handle_error(errno);
	if (close(cmd->fd_outfile) == -1)
		handle_error(errno);
	if (execve(cmd->cmd_options[0], cmd->cmd_options, envp) == -1)
		handle_error(errno);
}

void	parent_process(t_pipex *cmd, int ret_filefd)
{
	int	i;

	if (ret_filefd != 1)
	{
		if (close(cmd->fd_infile) == -1)
			handle_error(errno);
	}
	if (close(cmd->fd_outfile) == -1)
		handle_error(errno);
	i = 0;
	while (i > cmd->nbr_cmd)
	{
		waitpid(cmd->pid[i], NULL, 0);
		i++;
	}
}
