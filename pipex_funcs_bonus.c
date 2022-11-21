/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_funcs_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:47:48 by yamrire           #+#    #+#             */
/*   Updated: 2022/11/21 14:43:30 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_cluster(t_pipex *cmd, char **envp, int ret_filefd)
{
	cmd->pid = malloc(cmd->nbr_cmd * sizeof(pid_t));
	cmd->fd_tmp = -1;
	cmd->paths = arrange_paths(envp);
	if (pipe(cmd->fd_pip))
		handle_error(errno);
	if (ret_filefd != 1)
		in_process(cmd, cmd->cmd[0], &cmd->pid[0], envp);
}

void	middle_children(t_pipex *cmd, char **envp, int i)
{
	if (cmd->fd_tmp != -1)
		close(cmd->fd_tmp);
	cmd->fd_tmp = dup(cmd->fd_pip[0]);
	if (close(cmd->fd_pip[1]) == -1)
		handle_error(errno);
	if (close(cmd->fd_pip[0]) == -1)
		handle_error(errno);
	if (pipe(cmd->fd_pip))
		handle_error(errno);
	cmd->cmd_options = get_cmd_options(cmd, cmd->cmd[i]);
	if (!cmd->cmd_options)
	{
		ft_printf("pipex: %s:command not found\n", cmd->cmd[i]);
		return ;
	}
	cmd->pid[i] = fork();
	if (cmd->pid[i] == -1)
		handle_error(errno);
	else if (cmd->pid[i] == 0)
		mid_process(cmd, envp);
	else
		free_double(cmd->cmd_options);
}

void	last_cluster(t_pipex *cmd, char **envp, int ret_filefd, int i)
{
	if (cmd->fd_tmp != -1)
		close(cmd->fd_tmp);
	cmd->fd_tmp = dup(cmd->fd_pip[0]);
	if (cmd->fd_tmp == -1)
		handle_error(errno);
	if (close(cmd->fd_pip[0]) == -1)
		handle_error(errno);
	if (close(cmd->fd_pip[1]) == -1)
		handle_error(errno);
	cmd->cmd_options = get_cmd_options(cmd, cmd->cmd[i]);
	if (!cmd->cmd_options)
	{
		ft_printf("pipex: %s:command not found\n", cmd->cmd[i]);
		return ;
	}
	cmd->pid[i] = fork();
	if (cmd->pid[i] == -1)
		handle_error(errno);
	else if (cmd->pid[i] == 0)
		out_process(cmd, envp);
	else
	{
		free_double(cmd->cmd_options);
		parent_process(cmd, ret_filefd);
	}
}
