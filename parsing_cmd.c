/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 06:17:21 by yamrire           #+#    #+#             */
/*   Updated: 2022/06/29 06:01:26 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_double(char **pointer)
{
	int	i;

	i = 0;
	while (pointer[i])
	{
		free(pointer[i]);
		i++;
	}
	free (pointer);
	pointer = NULL;
}

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

char	**return_cmd_options(char **paths, char **cmd_options)
{
	char	*path_cmd;
	int		i;

	i = 0;
	while (paths[i])
	{
		path_cmd = ft_strjoin(paths[i], cmd_options[0]);
		if (access(path_cmd, F_OK | X_OK) == 0)
		{
			free_double(paths);
			free(cmd_options[0]);
			cmd_options[0] = ft_strdup(path_cmd);
			free(path_cmd);
			return (cmd_options);
		}
		free(path_cmd);
		i++;
	}
	free_double(paths);
	free_double(cmd_options);
	return (NULL);
}

char	**get_cmd_options(char *argv, char **envp)
{
	char	**cmd_options;
	char	**paths;

	paths = arrange_paths(envp);
	cmd_options = ft_split(argv, ' ');
	if (ft_strchr(cmd_options[0], '/'))
		return (cmd_options);
	return (return_cmd_options(paths, cmd_options));
}
