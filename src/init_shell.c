/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semin <semin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:11:04 by soum              #+#    #+#             */
/*   Updated: 2022/02/07 14:51:49 by semin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../Libft/libft.h"

void	init_struct(t_data *data, char **envp)
{
	// g_status = 0;
	data->lstlast = NULL;
	data->env = init_env(envp);
	setting_signal();
}

void	sigint_handler(int signal)
{
	pid_t	pid;
	int		status;

	(void)signal;
	pid = waitpid(-1, &status, WNOHANG);
	if (pid != -1)
	{
		printf("\n");
		return ;
	}
	printf("minishell$ \n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	// exit status: 130
}

void	sigquit_handler(int signal)
{
	pid_t	pid;
	int		status;

	(void)signal;
	pid = waitpid(-1, &status, WNOHANG);
	if (pid == -1)
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	printf("^\\Quit: 3\n");
	// exit status: 131
}

void	setting_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
