/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semin <semin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:53:23 by soum              #+#    #+#             */
/*   Updated: 2022/02/07 20:21:33 by soum             ###   ########.fr       */
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
void		ft_unset(t_cmd *cmd, t_env *env);

char		**make_envp(t_env *env);

int			ft_strcmp(const char *s1, const char *s2);

void		ft_export(t_cmd *cmd, t_env *env);

t_env		*new_env(char *envline);

void		ft_exit(t_cmd *cmd);

void		ft_cd(t_cmd *cmd, t_env *env);

t_env		*find_env(char *key, t_env *env);
// execute.c
void		execute(t_m_list *list, t_env *env);
void		execute_cmd(t_cmd *cmd, t_env *env);
void		execute_list(t_m_list *list, t_env *env, int b_stdin, int b_stdout);
//pipe.c
void		create_child(t_m_list *list, t_env *env);
void		child(t_m_list *list, t_env *env);

//redirection.c
int			rd_handler(t_cmd *cmd);

void		free_env_list(t_data *data);
void		free_envp(char **envp);
void		reparsing_env(t_data *data);
char		*cmdline_change(char *cmdline, t_env *env);
char		*replace_dollar(char *str, t_env *env);
int			sep_cnt_quote(char *cmd, char c);
void		putin(char *cmd, char *cmdline, int from, int i);
void		sep_cmdline(char *cmd, char c, char **cmdline);
char		**quote_split(char *cmd, char c);
char		*double_quote(char *cmdline, t_env *env);
char		*single_quote(char *cmdline);
int			get_keylen(char *str);
char		*dollar_sing(char *cmdline, t_env *env);
char		*mixed_quote(char *cmdline, t_env *env);
char		*ft_strjoin_free(char *s1, char *s2);
int			quote_index(char *cmd, char let, int *index);
char		*put_in_cmdline(char *cmd, char let, int *i);
char		*put_in_cmdline_normal(char *cmd, char let, int *i);
#endif
