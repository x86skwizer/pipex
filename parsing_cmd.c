/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 06:17:21 by yamrire           #+#    #+#             */
/*   Updated: 2022/06/28 00:38:26 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_paths(char **envp)
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
			break ;
		}
		i++;
	}
	paths = ft_split(path_var, ':');
	free(path_var);
	return (paths);
}

char	**arrange_paths(char **envp)
{
	char	**paths;
	char	*tmp;
	int		i;

	paths = get_paths(envp);
	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
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
	if (ft_strchr(cmd_options[0], '/'))
		return (cmd_options);
	while (paths[i])
	{
		path_cmd = ft_strjoin(paths[i], cmd_options[0]);
		if (access(path_cmd, F_OK | X_OK) == 0) 
		{
			i = 0;	
			while (paths[i])
				free(paths[i++]);
			free(cmd_options[0]);
			cmd_options[0] = ft_strdup(path_cmd);
			free(path_cmd);
			return (cmd_options);
		}
		free(path_cmd);
		i++;
	}
	i = 0;
	while (paths[i])
		free(paths[i++]);
	i = 0;
	while (cmd_options[i])
		free(cmd_options[i++]);
	return (NULL);
}
