/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 05:28:12 by yamrire           #+#    #+#             */
/*   Updated: 2022/06/25 05:37:34 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef	struct Pipex Pipex;
struct	Pipex
{
	int fd_infile;
	int fd_outfile;
	int fd_pip[2];
	char **cmd_options;
};


#endif