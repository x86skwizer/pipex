/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 00:01:23 by yamrire           #+#    #+#             */
/*   Updated: 2022/11/07 08:03:38 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft.h"
# include "ftprintf.h"

typedef struct s_pipex
{
	pid_t	*pid;
	int		nbr_cmd;
	int		fd_infile;
	int		fd_outfile;
	int		fd_pip[2];
	char	**cmd;
	char	**paths;
	int		fd_tmp;
}	pipex;

char **get_cmd_options(pipex *cmd, char *cmd_av);
char **get_paths(char **envp);
char **arrange_paths(char **envp);
void in_process(pipex *cmd, char *cmd_av, pid_t *pid, char **envp);
void mid_process(pipex *cmd, char *cmd_av, char **envp);
void out_process(pipex *cmd, char *cmd_av, char **envp);
void parent_process(pipex *cmd, int ret_filefd);
void handle_error(int static_code);

#endif