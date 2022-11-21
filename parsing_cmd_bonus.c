/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 07:56:32 by yamrire           #+#    #+#             */
/*   Updated: 2022/11/21 14:46:39 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**get_cmd_options(t_pipex *cmd, char *cmd_av)
{
	char	*path_cmd;
	char	**cmd_options;
	int		i;

	if (!cmd->paths)
		return (NULL);
	cmd_options = ft_split(cmd_av, ' ');
	if (!(ft_strchr(cmd_options[0], '/')))
	{
		i = 0;
		while (cmd->paths[i])
		{
			path_cmd = ft_strjoin(cmd->paths[i], cmd_options[0]);
			if (access(path_cmd, F_OK | X_OK) == 0)
			{
				free(cmd_options[0]);
				cmd_options[0] = ft_strdup(path_cmd);
				free(path_cmd);
				return (cmd_options);
			}
			free(path_cmd);
			i++;
		}
	}
	return (NULL);
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
	if (!path_var)
		return (NULL);
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
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(tmp, "/");
		free(tmp);
		i++;
	}
	return (paths);
}
