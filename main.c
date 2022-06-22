/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 04:05:03 by yamrire           #+#    #+#             */
/*   Updated: 2022/06/21 01:19:27 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "libft.h"
#include "libftprintf.h"

char	**get_cmd_options(char *argv)
{
	char	**cmd_options;

	if (argv)
		cmd_options = ft_split(argv, ' ');
	return (cmd_options);
}

char	*get_paths(char **envp)
{
	int		i;
	char	*paths;

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
	return (paths);
}

char	**arrage_paths(char *paths)
{
	char	**path_env;
	int		i;

	path_env = ft_split(paths, ':');
	i = 0;
	while (path_env[i])
	{
		path_env[i] = ft_strjoin(path_env[i], "/");
		i++;
	}
	return (path_env);
}

char	*find_path(char **path_env, char *cmd)
{
	char	*path_cmd;
	int		i;

	i = 0;
	while (path_env[i])
	{
		path_cmd = ft_strjoin(path_env[i], cmd);
		if (access(path_cmd, F_OK | X_OK) == 0)
			return (path_cmd);
		i++;
	}
	free(path_cmd);
	return (0);
}

int	main(int ac, char *av[], char **envp)
{

	char	*path = get_paths(envp);
	char	**str = arrage_paths(path);
	char	**cmd_options = get_cmd_options(av[1]);
	char	*cmd = find_path(str, cmd_options[0]);
	char	*options[3] = {"ls", "-la", NULL};
	int exe_num = execve("/usr/ls", options, envp);
	if (exe_num == -1)
		ft_printf("error : %s\n", strerror(errno));
	return (0);
}