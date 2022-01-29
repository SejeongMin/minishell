/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soum <soum@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:53:23 by soum              #+#    #+#             */
/*   Updated: 2022/01/29 17:46:42 by soum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

typedef struct s_m_list
{
	void *content;
	struct s_list *next;
}t_m_list;

typedef struct s_cmd
{
	char	**cmdline;
	int		flag;
	char	quote;
}	t_cmd;

typedef struct s_data
{
	char		*cmd_set;
	t_m_list	*lstlast;
	t_cmd	*cmd;
	char	*buff;
}	t_data;
//prompt.c
void	show_prompt(t_data *data);
//init_shell.c
void	init_struct(t_data *data);
void	setting_signal(void);
//check_cmd.c
int		check_cmd(t_data *data);
void	parsing_cmd(t_data *data);
#endif
