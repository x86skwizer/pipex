/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 05:28:12 by yamrire           #+#    #+#             */
/*   Updated: 2022/06/29 06:01:32 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft.h"
# include "ftprintf.h"

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd_infile;
	int		fd_outfile;
	int		fd_pip[2];
	char	**cmd_options;
}	t_Pipex;

char	**arrange_paths(char **envp);
char	**get_cmd_options(char *argv, char **envp);
void	in_process(t_Pipex *cmd, char *av, char **envp);
void	out_process(t_Pipex cmd, char *av, char **envp);
void	parent_process(t_Pipex cmd, int ret);
void	handle_error(int static_code);

#endif