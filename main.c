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

/* Function that returns every path possible */
char	**arrange_paths(char **envp)
{
	char	*paths;
	char	**path_split;
	int		i;

	i = 0;
	while (envp[i])
	{
		paths = ft_strnstr(envp[i], "PATH=", 5);
		if (paths)
		{
			paths = ft_substr(paths, 5, ft_strlen(paths) - 5);
			break;
		}
		i++;
	}
	path_split = ft_split(paths, ':');
	i = 0;
	while (path_split[i])
	{
		path_split[i] = ft_strjoin(path_split[i], "/");
		i++;
	}
	return (path_split);
}

/* Function that split the paths possible and add '/' at the end of every path */
// char	**arrange_paths(char *paths)
// {
// 	char	**path_env;
// 	int		i;

// 	path_env = ft_split(paths, ':');
// 	i = 0;
// 	while (path_env[i])
// 	{
// 		path_env[i] = ft_strjoin(path_env[i], "/");
// 		i++;
// 	}
// 	return (path_env);
// }

/* Function that separate the cmd in args and its options */
char	**get_cmd_options(char *argv)
{
	char	**cmd_options;

	cmd_options = ft_split(argv, ' ');
	return (cmd_options);
}

/* Function that find the right path for the cmd */
char	*find_path(char **paths, char *cmd_options)
{
	char	*path_cmd;
	int		i;
	

	i = 0;
	while (paths[i])
	{
		path_cmd = ft_strjoin(paths[i], cmd_options);
		if (access(path_cmd, F_OK | X_OK) == 0)
			return (path_cmd);
		i++;
	}
	free(path_cmd);
	return (0);
}

int	main(int ac, char *av[], char **envp)
{
	//char	*paths;
	char	**paths;
	int		fd_infile;
	int		fd_outfile;
	int		fd_pip[2];
	int		status1;
	char	**cmd_options1;
	char	*cmd1;
	char	**cmd_options2;
	char	*cmd2;


	if (ac == 5)
	{
		//paths = get_paths(envp);
		paths = arrange_paths(envp);
		fd_infile = open(av[1], O_RDONLY);
		fd_outfile = open(av[4], O_WRONLY | O_CREAT, 0666);
		pipe(fd_pip);
		pid_t	pid1 = fork();
		if (pid1 == 0)
		{
			close (fd_pip[0]);
			cmd_options1 = get_cmd_options(av[2]);
			cmd1 = find_path(paths, cmd_options1[0]);
			dup2(fd_infile, STDIN_FILENO);
			dup2(fd_pip[1], STDOUT_FILENO);
			close(fd_pip[1]);
			execve(cmd1, cmd_options1, envp);
			printf("execve failed 1");
		}
		else
		{
			pid_t pid2 = fork();
			if (pid2 == 0)
			{
				close (fd_pip[1]);
				cmd_options2 = get_cmd_options(av[3]);
				cmd2 = find_path(paths, cmd_options2[0]);
				dup2(fd_outfile, STDOUT_FILENO);
				dup2(fd_pip[0], STDIN_FILENO);
				close(fd_pip[0]);
				execve(cmd2, cmd_options2, envp);
				printf("execve failed 2");
			}
			else
			{
				close(fd_pip[0]);
				close(fd_pip[1]);
				while (1) {
					int ret = wait(&status1);
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