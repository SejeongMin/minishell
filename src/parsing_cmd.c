/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semin <semin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:51:05 by soum              #+#    #+#             */
/*   Updated: 2022/02/07 14:10:47 by soum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../Libft/libft.h"
#include <stdio.h>

int	key_len(char *str)
{
	int	len;

	len = 0;
	while (*str && *str != '$' && *str != ' ' && *str != '"' && *str != '\'')
	{
		str++;
		len++;
	}
	return (len);
}

char	*dollar_sign(char *cmdline, t_env *env)
{
	char	*new_cmdline;
	new_cmdline = double_quote(cmdline, env);
	return (new_cmdline);
}

char	*mixed_quote(char *cmdline, t_env *env)
{
	char	*new_cmdline;

	if (ft_strchr(cmdline, '\'') - cmdline < ft_strchr(cmdline, '"') - cmdline)
		new_cmdline = single_quote(cmdline);
	else
		new_cmdline = double_quote(cmdline, env);
	return (new_cmdline);
	//"'$USER'"
}

char	*double_quote(char *cmdline, t_env *env)
{
	char	*new_cmdline;
	char	let[2];
	int		index;

	index = 0;
	let[1] = 0;

	new_cmdline = (char *)malloc(sizeof(char));
	new_cmdline[0] = '\0';
	while (cmdline[index])
	{
		if (cmdline[index] == '$')
		{
			if (replace_dollar(&cmdline[index], env))
				new_cmdline = ft_strjoin_free(new_cmdline, replace_dollar(&cmdline[index], env));
			index += key_len(&cmdline[index + 1]);
		}
		else if (cmdline[index] != '"')
		{
			let[0] = cmdline[index];
			new_cmdline = ft_strjoin_free(new_cmdline, let);
		}
		index++;
	}
	return (new_cmdline);
}

char	*single_quote(char *cmdline)
{
	char	*new_cmdline;
	char	let[2];
	int		index;

	index = 0;
	let[1] = 0;
	new_cmdline = (char *)malloc(sizeof(char));
	new_cmdline[0] = '\0';
	while (cmdline[index])
	{
		if (cmdline[index] != '\'')
		{
			let[0] = cmdline[index];
			new_cmdline = ft_strjoin_free(new_cmdline, let);
		}
		index++;
	}
	return (new_cmdline);
}

char *cmdline_change(char *cmdline, t_env *env)
{
	char *tmp;
	(void)env;

	tmp = NULL;
	if (ft_strchr(cmdline, '\'') && ft_strchr(cmdline, '"'))
		tmp = mixed_quote(cmdline, env);
	else if (ft_strchr(cmdline, '"'))
		tmp = double_quote(cmdline, env);
	else if (ft_strchr(cmdline, '\''))
		tmp = single_quote(cmdline);
	else if (ft_strchr(cmdline, '$'))
		tmp = dollar_sign(cmdline, env);
	else
		return (cmdline);
	free(cmdline);
	return (tmp);
}

void	reparsing_env(t_data *data)
{
	t_m_list *list;
	int		index;
	char	**cmdline;

	list = data->lstlast;
	index = 0;
	while (list)
	{
		cmdline = list->content->cmdline;
		while (cmdline[index])
		{
			cmdline[index] = cmdline_change(cmdline[index], data->env);
			index++;
		}
		list = list->next;
	}
}

void	put_in_cmd(t_data *data, char *cmd, char let)
{
	t_cmd		*cmd_data;
	t_m_list	*list;
	t_m_list	*new_list;

	list = data->lstlast;
	new_list = (t_m_list *)malloc(sizeof(t_m_list));
	cmd_data = (t_cmd *)malloc(sizeof(t_cmd));
	//추가
	cmd_data->out = 0;
	if (ft_strrchr(cmd, '>'))
		cmd_data->out = 1;
	if (ft_strchr(cmd, '"') || ft_strchr(cmd, '\''))
		cmd_data->cmdline = quote_split(cmd, ' ');
	else
		cmd_data->cmdline = ft_split(cmd, ' ');
	if (let == '|')
		cmd_data->flag = 1;
	else if (let == ';' || let == '\0')
		cmd_data->flag = 0;
	new_list->content = cmd_data;
	new_list->next = NULL;
	if (list == NULL)
		data->lstlast = new_list;
	else
	{
		while (list->next)
			list = list->next;
		list->next = new_list;
	}
}

void	parsing_proc(t_data *data, char *tmp)
{
	int		i;
	int		j;
	char	*cmd;
	int		tmp_len;

	i = 0;
	j = 0;
	tmp_len = ft_strlen(tmp);
	while (i <= tmp_len)
	{
		if (tmp[i] == '\0' && (tmp[i -1] == ';' || tmp[i -i] == '|'))
			break;
		if (tmp[i] == ';' || tmp[i] == '|' || tmp[i] == '\0')
		{
			cmd = (char *)malloc(sizeof(char) * (i - j + 1));
			ft_strlcpy(cmd, tmp + j, i - j + 1);
			j = i + 1;
			put_in_cmd(data, cmd, tmp[i]);
			free(cmd);
		}
		i++;
	}
}

void	parsing(t_data *data)
{
	char	*tmp;

	tmp = data->cmd_set;
	parsing_proc(data, tmp);
	reparsing_env(data);
	// execute_list(data->lstlast, data->env);
	execute(data->lstlast, data->env);
//	execute_cmd(data->lstlast->content, data->env);
}
