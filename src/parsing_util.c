/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soum <soum@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:11:52 by soum              #+#    #+#             */
/*   Updated: 2022/02/05 18:23:58 by soum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../Libft/libft.h"

int	sep_cnt_quote(char *cmd, char c)
{
	int quote_flag;
	int	cnt;
	int	index;

	cnt = 0;
	index = 0;
	quote_flag = 0;
	while (cmd[index])
	{
		if (cmd[index] == '"')
		{
			index++;
			cnt++;
			while (cmd[index] && cmd[index] != '"')
				index++;
		}
		else if (cmd[index] == '\'')
		{
			index++;
			cnt++;
			while (cmd[index] && cmd[index] != '\'')
				index++;
		}
		else if (cmd[index] != c)
		{
			index++;
			cnt++;
			while (cmd[index] && cmd[index] != c)
				index++;
		}
		index++;
	}
	return (cnt);
}

void 	putin(char *cmd, char *cmdline, int from, int i)
{
	int index;

	index = 0;
	while (from < i)
	{
		cmdline[index] = cmd[from];
		index++;
		from++;
	}
	cmdline[index] = '\0';
}

void	sep_cmdline(char *cmd, char c, char **cmdline)
{
	int index;
	int i;
	int from;

	index = 0;
	i = 0;
	from = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"')
		{
			i++;
			from = i - 1;
			while (cmd[i] && cmd[i] != '"')
				i++;
			cmdline[index] = (char *)malloc((i - from + 1) * sizeof(char));
			putin(cmd, cmdline[index], from, i + 1);
			index++;
		}
		else if (cmd[i] == '\'')
		{
			i++;
			from = i - 1;
			while (cmd[i] && cmd[i] != '\'')
				i++;
			cmdline[index] = (char *)malloc((i - from + 1) * sizeof(char));
			putin(cmd, cmdline[index], from, i + 1);
			index++;
		}
		else if (cmd[i] != c)
		{
			i++;
			from = i - 1;
			while (cmd[i] && cmd[i] != c)
				i++;
			cmdline[index] = (char *)malloc((i - from + 1) * sizeof(char));
			putin(cmd, cmdline[index], from, i);
			index++;
		}
		i++;
	}
}

char	**quote_split(char *cmd, char c)
{
	char **cmdline;
	int		sep_cnt;

	sep_cnt = sep_cnt_quote(cmd, c);
	cmdline = (char **)malloc(sizeof(char *) * (sep_cnt + 1));
	if (!cmdline)
		return (NULL);
	sep_cmdline(cmd, c, cmdline);
	cmdline[sep_cnt] = NULL;
	return (cmdline);
}
