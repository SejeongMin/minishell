#include "../includes/minishell.h"
#include "../Libft/libft.h"

int	redirection(char *file, int type, int dup_out, int out)
{
	int	backup;

	backup = dup(1);
	if (type == 1)
		return (rd_in(file));
	else if (type == 2)
		return (rd_out(file));
	else if (type == 3)
		return (rd_double_out(file));
	else
	{
		if (out)
			dup2(dup_out, 1);
		heredoc(file);
		if (out)
			dup2(backup, 1);
		rd_in("heredocfile");
		unlink("heredocfile");
	}
	close(backup);
	return (0);
}

int	cmd_cnt(t_cmd *cmd)
{
	int	idx;
	int	ret;

	idx = 0;
	ret = 0;
	while (cmd->cmdline[idx])
	{
		if (!ft_strcmp(cmd->cmdline[idx], ">")
			|| !ft_strcmp(cmd->cmdline[idx], "<")
			|| !ft_strcmp(cmd->cmdline[idx], ">>")
			|| !ft_strcmp(cmd->cmdline[idx], "<<"))
			ret++;
		idx++;
	}
	return (idx - (ret * 2));
}

int	find_rd_type(char *rd)
{
	if (!ft_strcmp(rd, "<"))
		return (1);
	else if (!ft_strcmp(rd, ">"))
		return (2);
	else if (!ft_strcmp(rd, ">>"))
		return (3);
	else if (!ft_strcmp(rd, "<<"))
		return (4);
	else
		return (0);
}

int	redirect(t_cmd *cmd, char **cmdline, char **new_cmdline, int dup_out)
{
	int		idx;
	int		new_idx;
	int		rd_type;
	int		status;

	idx = -1;
	new_idx = 0;
	while (cmdline[++idx])
	{
		rd_type = find_rd_type(cmdline[idx]);
		if (rd_type)
		{
			status = redirection(cmdline[++idx], rd_type, dup_out, cmd->out);
			if (status && rd_type == 1)
			{
				dup2(dup_out, 1);
				printf("minishell: %s: %s\n", cmdline[idx], strerror(errno));
				break ;
			}
		}
		else
			new_cmdline[new_idx++] = ft_strdup(cmdline[idx]);
	}
	new_cmdline[new_idx] = 0;
	return (status);
}

int	rd_handler(t_cmd *cmd)
{
	char	**new_cmdline;
	int		status;
	int		dup_out;

	status = 0;
	dup_out = dup(1);
	new_cmdline = (char **)malloc(sizeof(char *) * (cmd_cnt(cmd) + 1));
	status = redirect(cmd, cmd->cmdline, new_cmdline, dup_out);
	free_envp(cmd->cmdline);
	cmd->cmdline = new_cmdline;
	close(dup_out);
	return (status);
}
