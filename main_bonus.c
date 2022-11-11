/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 00:00:56 by yamrire           #+#    #+#             */
/*   Updated: 2022/11/11 10:53:32 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	auto_fill(t_pipex *cmd, int ac, char **av)
{
	int	i;

	cmd->nbr_cmd = ac - 3;
	cmd->cmd = malloc(sizeof(char *) * (cmd->nbr_cmd + 1));
	i = 0;
	while (i < cmd->nbr_cmd)
	{
		cmd->cmd[i] = ft_strdup(av[ac - cmd->nbr_cmd - 1 + i]);
		i++;
	}
	cmd->cmd[i] = NULL;
}

void	here_doc(t_pipex *cmd, char *av)
{
	char	*here_doc;
	char	*limiter;

	limiter = ft_strjoin(av, "\n");
	while (1)
	{
		ft_printf("pipex here_doc> ");
		here_doc = get_next_line(0);
		if (cmpstr(limiter, here_doc))
		{
			free(here_doc);
			free(limiter);
			break ;
		}
		if (write(cmd->fd_infile, here_doc, ft_strlen(here_doc)) == -1)
			handle_error(errno);
		free(here_doc);
	}
}

void	here_doc_fill(t_pipex *cmd, char **av, int *ret_filefd)
{
	*ret_filefd = open_heredoc(cmd, av[5]);
	here_doc(cmd, av[2]);
	if (close(cmd->fd_infile) == -1)
		handle_error(errno);
	cmd->fd_infile = open("/tmp/.here_doc", O_RDONLY);
	if (cmd->fd_infile == -1)
		handle_error(errno);
	cmd->nbr_cmd = 2;
	cmd->cmd = malloc(sizeof(char *) * (cmd->nbr_cmd + 1));
	cmd->cmd[0] = ft_strdup(av[3]);
	cmd->cmd[1] = ft_strdup(av[4]);
	cmd->cmd[2] = NULL;
}

int	main(int ac, char *av[], char **envp)
{
	t_pipex	cmd;
	int		i;
	int		ret_filefd;

	if (ac >= 5)
	{
		if (ac == 6 && cmpstr(av[1], "here_doc"))
			here_doc_fill(&cmd, av, &ret_filefd);
		else
		{
			auto_fill(&cmd, ac, av);
			ret_filefd = open_files(&cmd, ac, av);
		}
		first_cluster(&cmd, envp, ret_filefd);
		i = 1;
		if (cmd.nbr_cmd > 2)
		{
			while (i < cmd.nbr_cmd - 1)
				middle_children(&cmd, envp, i++);
		}
		last_cluster(&cmd, envp, ret_filefd, i);
	}
	else
		ft_printf("ERROR : INCORRECT ARGUMENTS !\n");
	return (0);
}
