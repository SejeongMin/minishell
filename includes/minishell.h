/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semin <semin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:53:23 by soum              #+#    #+#             */
/*   Updated: 2022/02/07 17:38:29 by semin            ###   ########.fr       */
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
# include <fcntl.h>
# include <errno.h>
# include <string.h>

typedef struct s_m_list
{
	struct s_cmd	*content;
	struct s_m_list	*next;
}t_m_list;

typedef struct s_cmd
{
	char	**cmdline;
	int		flag;
	char	quote;
	int		fd[2];
	int		out;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	int			status;
	char		*cmd_set;
	t_m_list	*lstlast;
	t_env		*env;

}	t_data;

extern int	g_status;

//prompt.c
void		show_prompt(t_data *data);
//init_shell.c
void		init_struct(t_data *data, char **envp);
void		setting_signal(void);
//check_cmd.c
int			check_cmd(t_data *data);
//error.c
void		error_msg(char *str);
//parsing_cmd.c
void		parsing(t_data *data);
void		parsing_proc(t_data *data, char *tmp);
void		put_in_cmd(t_data *data, char *cmd, char let);
//free_list.c
void		free_cmd_list(t_data *data);
//env.c
t_env		*init_env(char **envp);
void		ft_export(t_cmd *cmd, t_env *env);
void		ft_unset(t_cmd *cmd, t_env *env, t_data *data);

char		**make_envp(t_env *env);

int			ft_strcmp(const char *s1, const char *s2);

void		ft_export(t_cmd *cmd, t_env *env);

t_env		*new_env(char *envline);

void		ft_exit(t_cmd *cmd, int flag, t_data *data);

void		ft_cd(t_cmd *cmd, t_env *env);

t_env		*find_env(char *key, t_env *env);
// execute.c
void		execute(t_data *data, t_m_list *list);

void		execute_cmd(t_data *data, t_cmd *cmd, t_env *env, int flag);
void		execute_list(t_m_list *list, t_data *data, int b_stdin, int b_stdout);
//pipe.c
void		create_child(t_m_list *list, t_data *data, int prev);
void		child(t_m_list *list, t_data *data);

//redirection.c
int			rd_handler(t_cmd *cmd);

//rd_util.c
int			rd_in(char *file);
int			rd_out(char *file);
int			rd_double_out(char *file);
void		heredoc(char *end);
int			find_rd_type(char *rd);

void		free_env_list(t_data *data);
void		free_envp(char **envp);

#endif
