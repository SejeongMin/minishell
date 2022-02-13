/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semin <semin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 01:23:33 by semin             #+#    #+#             */
/*   Updated: 2022/02/14 01:23:37 by semin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../Libft/libft.h"

void	hd_handler(int signal)
{
	if (signal == SIGINT)
		exit(-2);
	else if (signal == SIGQUIT)
		return ;
}

void	heredoc_child(int *fd, char *end)
{
	char	*line;

	signal(SIGINT, hd_handler);
	signal(SIGQUIT, hd_handler);
	close(fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, end))
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
}

int	heredoc(char *end)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		heredoc_child(fd, end);
		exit(0);
	}
	waitpid(pid, &status, 0);
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	return ((int)(status >> 8));
}
