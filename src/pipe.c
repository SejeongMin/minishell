#include "../includes/minishell.h"
#include "../Libft/libft.h"

void	child(t_m_list *list, t_env *env)
{
	t_cmd	*cmd;

	cmd = list->content;
	close(cmd->fd[0]);
	if (cmd->flag == 1)
	{
		dup2(cmd->fd[1], STDOUT_FILENO);
		close(cmd->fd[1]);
	}
	execute_cmd(cmd, env);
	exit(0);
}

void	create_child(t_m_list *list, t_env *env)
{
	pid_t	pid;
	int		status;

	if (pipe(list->content->fd) < 0)
	{
		printf("pipe error");
		return ;
	}
	// if (prev == 1)
	// 	dup2(STDIN_FILENO, list->content->fd[1]);
		// dup2(400, STDIN_FILENO);
	pid = fork();
	if (pid == 0)
		child(list, env);
	else
	{
		waitpid(pid, &status, 0);
		close(list->content->fd[1]);
		if (list->content->flag == 1)
			dup2(list->content->fd[0], list->next->content->fd[1]);
			// dup2(list->content->fd[0], 400);
		close(list->content->fd[0]);
	}
}
