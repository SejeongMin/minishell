/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semin <semin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:51:05 by soum              #+#    #+#             */
/*   Updated: 2022/02/09 17:31:59 by soum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../Libft/libft.h"

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

int		parsing_proc(t_data *data, char *tmp)
{
	int		i;
	int		j;
	char	*cmd;

	i = 0;
	j = 0;
	while (tmp[i])
	{
		while (tmp[i] && tmp[i] != ';' && tmp[i] != '|')
		{
			i = find_quote_match(tmp, i);
			if (i == -1)
				return (1);
		}
		cmd = (char *)malloc(sizeof(char) *(i - j + 1));
		ft_strlcpy(cmd, tmp + j, i - j + 1);
		j = i + 1;
		put_in_cmd(data, cmd, tmp[i]);
		free(cmd);
		if (tmp[i])
			i++;
	}
	return (0);
}

void	parsing(t_data *data)
{
	char	*tmp;

	tmp = data->cmd_set;
	if (parsing_proc(data, tmp))
	{
		error_msg("minishell: syntax error: unexpected end of file\n");
		return ;
	}
	if (pipe_error_check(data))
		return ;
	reparsing_env(data);
	execute(data, data->lstlast);
}
