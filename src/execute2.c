/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semin <semin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 04:10:03 by semin             #+#    #+#             */
/*   Updated: 2022/02/02 14:14:36 by soum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../Libft/libft.h"

void	exec_extern(t_cmd *cmd, char **env)
{
	char	*command[6];
	int		i;

	command[0] = ft_strjoin("/bin/", cmd->cmdline[0]);
	command[1] = ft_strjoin("/usr/bin/", cmd->cmdline[0]);
	command[2] = ft_strjoin("/usr/local/bin/", cmd->cmdline[0]);
	command[3] = ft_strjoin("/usr/sbin/", cmd->cmdline[0]);
	command[4] = ft_strjoin("/sbin/", cmd->cmdline[0]);
	command[5] = 0;
	i = 0;
	while (i < 5)
	{
		execve(command[i], cmd->cmdline, env);
		i++;
	}
	printf("minishell: %s: command not found\n", cmd->cmdline[0]);
	// exit 정보 저장
}

void execute_extern(t_cmd *cmd, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
		exec_extern(cmd, env);
		exit(0);
		// exit status 필요
	}
	else
	{
		waitpid(pid, &status, 0);
		// printf("status: %d\n", status >> 9);
		// env free
	}
}

void	execute_cmd(t_cmd *cmd, t_env *env)
{
	if (!ft_strcmp(cmd->cmdline[0], "export"))
		ft_export(cmd, env);
	// else if (!ft_strcmp(cmd->cmdline[0], "echo"))
	// 	printf("echo\n");
	else if (!ft_strcmp(cmd->cmdline[0], "cd"))
		ft_cd(cmd, env);
	else if (!ft_strcmp(cmd->cmdline[0], "unset"))
		ft_unset(cmd, env);
	else if (!ft_strcmp(cmd->cmdline[0], "exit"))
		ft_exit(cmd);
	else
		execute_extern(cmd, make_envp(env));
}

t_m_list	*execute(t_m_list *list, t_env *env)
{
	t_cmd	*cmd;

	cmd = list->content;
	if (cmd->flag == 1) //pipe O
		set_pipe(list, env);
	else
		execute_cmd(cmd, env);
	return (list->next);
}

void	execute_list(t_m_list *list, t_env *env) //list 실행
{
	t_m_list	*cur;

	cur = list;
	while (cur)
	{
		cur = execute(cur, env);
	}
}

// 테스트용
int	wdcount(char const *s, char c)
{
	int	wd;

	wd = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		if (*s != c)
		{
			wd++;
			while (*s != c && *s)
				s++;
		}
		if (*s)
			s++;
	}
	return (wd);
}
/*
void	parsing(char *line, t_env *env)
{
	t_cmd	*cmd;

	int ac = wdcount(line, ' ');
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->cmdline = (char **)malloc(sizeof(char *) * (ac + 1));
	cmd->cmdline = ft_split(line, ' ');
	cmd->flag = 0;

	execute_cmd(cmd, env);
	free(cmd->cmdline);
	free(cmd);
}
*/
