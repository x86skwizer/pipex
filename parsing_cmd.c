/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 06:17:21 by yamrire           #+#    #+#             */
/*   Updated: 2022/06/25 06:23:56 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
