/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semin <semin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 04:10:03 by semin             #+#    #+#             */
/*   Updated: 2022/02/06 23:48:26 by soum             ###   ########.fr       */
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
	exit(127);
	// exit 정보 저장
}

void	execute_extern(t_cmd *cmd, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		exit(errno);
	if (pid == 0)
	{
		exec_extern(cmd, env);
		// exit status 필요
	}
	else
	{
		waitpid(pid, &status, 0);
		// printf("status: %d\n", status >> 9);
		// env free
		free_envp(env);
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

void	execute_list(t_m_list *list, t_env *env, int b_stdin, int b_stdout)
{
	t_m_list	*cur;
	int			prev;

	cur = list;
	prev = 0;
	while (cur)
	{
		if (cur->content->flag == 1)
			create_child(cur, env);
		else if (prev == 1)
			create_child(cur, env);
		else
		{
			if (!rd_handler(cur->content))
				execute_cmd(cur->content, env);
		}
		prev = cur->content->flag;
		if (prev == 0)
		{
			dup2(b_stdin, 0);
			dup2(b_stdout, 1);
		}
		cur = cur->next;
	}
}

void	execute(t_m_list *list, t_env *env)
{
	t_m_list	*cur;
	int			prev;
	int stdin_dup;
	int stdout_dup;

	stdin_dup = dup(0);
	stdout_dup = dup(1);
	cur = list;
	prev = 0;
	execute_list(list, env, stdin_dup, stdout_dup);
	dup2(stdin_dup, 0);
	dup2(stdout_dup, 1);
	close(stdin_dup);
	close(stdout_dup);
}
