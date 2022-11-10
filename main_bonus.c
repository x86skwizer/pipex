/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 00:00:56 by yamrire           #+#    #+#             */
/*   Updated: 2022/11/09 11:41:12 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int cmpstr(const char *s1, const char *s2)
{
	size_t len1;
	size_t len2;
	size_t n;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	n = 0;
	if (len1 != len2)
		return (0);
	while (n < len1)
	{
		if (s1[n] != s2[n])
			return (0);
		n++;
	}
	return (1);
}

void handle_error(int static_code)
{
	perror("pipex");
	exit(static_code);
}

void free_double(char **pointer)
{
	int i;

	i = 0;
	while (pointer[i])
	{
		free(pointer[i]);
		i++;
	}
	free(pointer);
	pointer = NULL;
}

int	open_heredoc(pipex *cmd, char *av)
{
	cmd->fd_infile = open("/tmp/.here_doc", O_APPEND | O_CREAT | O_RDWR | O_TRUNC, 0644);
	cmd->fd_outfile = open(av, O_APPEND | O_CREAT | O_RDWR, 0644);
	if (cmd->fd_infile == -1)
	{
		perror("pipex");
		return (1);
	}
	if (cmd->fd_outfile == -1)
		handle_error(errno);
	return (0);
}

int open_files(pipex *cmd, int ac, char **av)
{
	cmd->fd_infile = open(av[1], O_RDONLY);
	cmd->fd_outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_infile == -1)
	{
		perror("pipex");
		return (1);
	}
	if (cmd->fd_outfile == -1)
		handle_error(errno);
	return (0);
}

int main(int ac, char *av[], char **envp)
{
	pipex	cmd;
	int		i;
	int		ret_filefd;
	char	*here_doc;
	char	*limiter;

	if (ac >= 5)
	{
		if (ac == 6 && cmpstr(av[1], "here_doc"))
		{
			ret_filefd = open_heredoc(&cmd, av[5]);
			limiter = ft_strjoin(av[2], "\n");
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
				write(cmd.fd_infile, here_doc, ft_strlen(here_doc));
				//protection needed
				free(here_doc);
			}
			close(cmd.fd_infile);
			//protection needed
			cmd.fd_infile = open("/tmp/.here_doc", O_RDONLY);
			//protection needed
			cmd.nbr_cmd = 2;
			cmd.cmd = malloc(sizeof(char *) * (cmd.nbr_cmd + 1));
			cmd.cmd[0] = ft_strdup(av[3]);
			cmd.cmd[1] = ft_strdup(av[4]);
			cmd.cmd[2] = NULL;
		}
		else
		{
			cmd.nbr_cmd = ac - 3;
			cmd.cmd = malloc(sizeof(char *) * (cmd.nbr_cmd + 1));
			i = 0;
			while (i < cmd.nbr_cmd)
			{
				cmd.cmd[i] = ft_strdup(av[ac - cmd.nbr_cmd - 1 + i]);
				i++;
			}
			cmd.cmd[i] = NULL;
			ret_filefd = open_files(&cmd, ac, av);
		}
		cmd.pid = malloc(cmd.nbr_cmd * sizeof(pid_t));
		cmd.fd_tmp = -1;
		cmd.paths = arrange_paths(envp);
		if (pipe(cmd.fd_pip))
			handle_error(errno);
		if (ret_filefd != 1)
			in_process(&cmd, cmd.cmd[0], &cmd.pid[0], envp);
		i = 1;
		if (cmd.nbr_cmd > 2)
		{
			while (i < cmd.nbr_cmd - 1)
			{
				if (cmd.fd_tmp != -1) {
					close(cmd.fd_tmp);
				}
				cmd.fd_tmp = dup(cmd.fd_pip[0]);
				if (close(cmd.fd_pip[1]) == -1)
					handle_error(errno);
				if (close(cmd.fd_pip[0]) == -1)
					handle_error(errno);
				if (pipe(cmd.fd_pip))
					handle_error(errno);
				cmd.pid[i] = fork();
				if (cmd.pid[i] == -1)
					handle_error(errno);
				else if (cmd.pid[i] == 0)
					mid_process(&cmd, cmd.cmd[i], envp);
				i++;
			}
		}
		if (cmd.fd_tmp != -1)
			close(cmd.fd_tmp);
		cmd.fd_tmp = dup(cmd.fd_pip[0]);
		if (close(cmd.fd_pip[0]) == -1)
			handle_error(errno);
		if (close(cmd.fd_pip[1]) == -1)
			handle_error(errno);
		cmd.pid[i] = fork();
		if (cmd.pid[i] == -1)
			handle_error(errno);
		else if (cmd.pid[i] == 0)
			out_process(&cmd, cmd.cmd[i], envp);
		else
			parent_process(&cmd, ret_filefd);
	}
	else
		ft_printf("ERROR : INCORRECT ARGUMENTS !\n");
	return (0);
}
