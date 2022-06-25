/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 05:28:12 by yamrire           #+#    #+#             */
/*   Updated: 2022/06/25 06:23:47 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include "libft.h"
#include "ftprintf.h"

typedef	struct Pipex Pipex;
struct	Pipex
{
	int fd_infile;
	int fd_outfile;
	int fd_pip[2];
	char **cmd_options;
};

char	**arrange_paths(char **envp);
char	**get_cmd_options(char *argv, char **envp);


#endif