#include "../includes/minishell.h"
#include "../Libft/libft.h"

void	rd_in(char *file)
{
	int	newfd;

	newfd = open(file, O_RDONLY, 0644);
	if (newfd < 1)
	{
		printf("minishell: %s: %s\n", file, strerror(errno));
		return ;
		//free
	}
	dup2(newfd, 0);
	close(newfd);
}

void	rd_out(char *file)
{
	int	newfd;

	newfd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (newfd < 1)
	{
		printf("minishell: %s: %s\n", file, strerror(errno));
		return ;
		//free
	}
	dup2(newfd, 1);
	close(newfd);
}

void	rd_double_out(char *file)
{
	int	newfd;

	newfd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (newfd < 1)
	{
		printf("minishell: %s: %s\n", file, strerror(errno));
		return ;
		//free
	}
	dup2(newfd, 1);
	close(newfd);
}

void	heredoc(char *end)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, end))
		{
			free(line);
			break ;
		}
	}
}

void	redirection(char *file, int type)
{
	if (type == 1) // <
		rd_in(file);
	else if (type == 2) // >
		rd_out(file);
	else if (type == 3) // >>
		rd_double_out(file);
	else
		return ;
	// else
		// heredoc(cmd, file);
}

int	cmd_cnt(t_cmd *cmd)
{
	int	idx;
	int	ret;

	idx = 0;
	ret = 0;
	while (cmd->cmdline[idx])
	{
		if (!ft_strcmp(cmd->cmdline[idx], ">") ||
			!ft_strcmp(cmd->cmdline[idx], "<") ||
			!ft_strcmp(cmd->cmdline[idx], ">>") ||
			!ft_strcmp(cmd->cmdline[idx], "<<"))
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

void	free_cmdline(char **cmdline)
{
	int		index;

	index = 0;
	while (cmdline[index])
	{
		free(cmdline[index]);
		index++;
	}
	free(cmdline[index]);
	free(cmdline);
}

void	rd_handler(t_cmd *cmd, t_env *env)
{
	char	**new_cmdline;
	int		idx;
	int		new_idx;
	int		rd_type;

	idx = 0;
	new_idx = 0;
	new_cmdline = (char **)malloc(sizeof(char *) * (cmd_cnt(cmd) + 1));
	while (cmd->cmdline[idx])
	{
		rd_type = find_rd_type(cmd->cmdline[idx]);
		if (rd_type)
		{
			printf("rdtype : %d\n", rd_type);
			redirection(cmd->cmdline[idx + 1], rd_type);
			idx++;
		}
		else
		{
			new_cmdline[new_idx] = ft_strdup(cmd->cmdline[idx]);
			new_idx++;
		}
		idx++;
	}
	new_cmdline[new_idx] = 0;
	free_cmdline(cmd->cmdline);
	cmd->cmdline = new_cmdline;
	if (!errno)
		execute_cmd(cmd, env);
}
