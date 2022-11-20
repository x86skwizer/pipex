/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 00:01:23 by yamrire           #+#    #+#             */
/*   Updated: 2022/11/20 17:44:40 by yamrire          ###   ########.fr       */
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
# include "ft_printf.h"

typedef struct s_pipex
{
	pid_t	*pid;
	int		nbr_cmd;
	int		fd_infile;
	int		fd_outfile;
	int		fd_pip[2];
	char	**cmd;
	char	**paths;
	char	**cmd_options;
	int		fd_tmp;
}	t_pipex;

char	**get_cmd_options(t_pipex *cmd, char *cmd_av);
char	**get_paths(char **envp);
char	**arrange_paths(char **envp);
void	in_process(t_pipex *cmd, char *cmd_av, pid_t *pid, char **envp);
void	mid_process(t_pipex *cmd, char **envp);
void	out_process(t_pipex *cmd, char **envp);
void	parent_process(t_pipex *cmd, int ret_filefd);
void	handle_error(int static_code);
char	*get_next_line(int fd);
void	free_double(char **pointer);
int		open_heredoc(t_pipex *cmd, char *av);
int		open_files(t_pipex *cmd, int ac, char **av);
int		cmpstr(const char *s1, const char *s2);
void	handle_error(int static_code);
void	first_cluster(t_pipex *cmd, char **envp, int ret_filefd);
void	middle_children(t_pipex *cmd, char **envp, int i);
void	last_cluster(t_pipex *cmd, char **envp, int ret_filefd, int i);

#endif