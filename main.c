/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semin <semin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:54:17 by soum              #+#    #+#             */
/*   Updated: 2022/02/01 23:10:04 by semin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"
#include "./Libft/libft.h"

void	handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("minishell$ \n");
		if (rl_on_new_line() == -1) // move to new(empty) line
			exit(1);
		rl_replace_line("", 1); // 문자 입력 후 ctrl+c 눌렀을 때 버퍼 비워줌
		rl_redisplay(); // readline redisplay
	}
}

int main(int ac, char **av, char **envp)
{
	char *str;
	struct termios term;
	(void)ac;
	(void)av;

	t_env	*env;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);	// 제어문자 반향 off
	// term.c_cc[VMIN] = 1;	// minimum number of bytes in input queue
	// term.c_cc[VTIME] = 0;	// how long to wait
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	env = init_env(envp);
	//env 초기화

	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
		{
			printf("exit\n");
			exit(-1);
		}
		else if (str[0] == '\0')
			free(str);
		else
		{
			add_history(str);
			parsing(str, env);
			free(str);
		}
	}
}
