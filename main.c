/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 04:05:03 by yamrire           #+#    #+#             */
/*   Updated: 2022/06/24 21:16:32 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include "libft.h"
#include "libftprintf.h"

char	**arrange_paths(char **envp)
{
	char	*path_var;
	char	**paths;
	int		i;

	i = 0;
	while (envp[i])
	{
		path_var = ft_strnstr(envp[i], "PATH=", 5);
		if (path_var)
		{
			path_var = ft_substr(path_var, 5, ft_strlen(path_var) - 5);
			break;
		}
		i++;
	}
	paths = ft_split(path_var, ':');
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	return (paths);
}


char	**get_cmd_options(char *argv, char **envp)
{
	char	**cmd_options;
	char	*path_cmd;
	char	**paths;
	int		i;

	paths = arrange_paths(envp);
	cmd_options = ft_split(argv, ' ');
	i = 0;
	while (paths[i])
	{
		path_cmd = ft_strjoin(paths[i], cmd_options[0]);
		if (access(path_cmd, F_OK | X_OK) == 0)
			break;
		i++;
	}
	cmd_options[0] = ft_strdup(path_cmd);
	return (cmd_options);
}

int	main(int ac, char *av[], char **envp)
{
	int		fd_infile;
	int		fd_outfile;
	int		fd_pip[2];
	pid_t	pid1;
	pid_t	pid2;
	char	**cmd_options1;
	char	**cmd_options2;


	if (ac == 5)
	{
		fd_infile = open(av[1], O_RDONLY);
		fd_outfile = open(av[4], O_WRONLY | O_CREAT, 0666);
		pipe(fd_pip);
		pid1 = fork();
		if (pid1 == 0)
		{
			close (fd_pip[0]);
			cmd_options1 = get_cmd_options(av[2], envp);
			dup2(fd_infile, STDIN_FILENO);
			dup2(fd_pip[1], STDOUT_FILENO);
			close(fd_pip[1]);
			execve(cmd_options1[0], cmd_options1, envp);
		}
		else
		{
			pid2 = fork();
			if (pid2 == 0)
			{
				close (fd_pip[1]);
				cmd_options2 = get_cmd_options(av[3], envp);
				dup2(fd_outfile, STDOUT_FILENO);
				dup2(fd_pip[0], STDIN_FILENO);
				close(fd_pip[0]);
				execve(cmd_options2[0], cmd_options2, envp);
			}
			else
			{
				close(fd_pip[0]);
				close(fd_pip[1]);
				while (1) {
					int ret = wait(0);
					if (ret == -1)
						break;
				}

				close(fd_infile);
				close(fd_outfile);
				exit(0);
			}
		}
	}
	else
		ft_printf("ERROR : Wrong parameters !\n");

		
	return (0);
}