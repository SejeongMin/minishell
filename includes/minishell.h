/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semin <semin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:53:23 by soum              #+#    #+#             */
/*   Updated: 2022/02/01 00:22:47 by semin            ###   ########.fr       */
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
# include <sys/stat.h>

typedef struct s_m_list
{
	void			*content;
	struct s_list	*next;
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
	t_cmd		*cmd;
	char		*buff;
}	t_data;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// execute
void	parsing(char *line, t_env *env);

// env.c
t_env	*init_env(char **envp);

void	ft_export(t_cmd *cmd, t_env *env);

void	ft_unset(t_cmd *cmd, t_env *env);

char	**make_envp(t_env *env);

int	ft_strcmp(const char *s1, const char *s2);

void	ft_export(t_cmd *cmd, t_env *env);

t_env	*new_env(char *envline);

void	ft_exit(t_cmd *cmd);

void	ft_cd(t_cmd *cmd, t_env *env);


#endif
