/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semin <semin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:src/echo.c
/*   Created: 2022/02/01 01:30:27 by semin             #+#    #+#             */
/*   Updated: 2022/02/01 01:43:24 by semin            ###   ########.fr       */
========
/*   Created: 2022/01/11 12:53:23 by soum              #+#    #+#             */
/*   Updated: 2022/02/01 23:23:35 by semin            ###   ########.fr       */
>>>>>>>> main:includes/minishell.h
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../Libft/libft.h"

<<<<<<<< HEAD:src/echo.c
// void	ft_echo(t_cmd *cmd)
// {
// 	return ;
// }
========
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
	struct s_m_list	*next;
}	t_m_list;

typedef struct s_cmd
{
	char	**cmdline;
	int		flag;
	char	quote;
	//추가
	int		fd[2];
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

t_env	*find_env(char *key, t_env *env);

t_m_list	*execute(t_m_list *list, t_env *env);
void	execute_cmd(t_cmd *cmd, t_env *env);
void	execute_list(t_m_list *list, t_env *env);

void	set_pipe(t_m_list *list, t_env *env);

#endif
>>>>>>>> main:includes/minishell.h
