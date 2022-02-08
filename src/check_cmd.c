/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soum <soum@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:41:40 by soum              #+#    #+#             */
/*   Updated: 2022/02/08 15:28:01 by soum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../Libft/libft.h"

int pipe_error_check2(t_m_list *tmp, int flag)
{
    if (flag == 1)
    {
        if (tmp->next && tmp->next->content->flag \
                && tmp->next->content->cmdline[0] == NULL)
        {
            syntax_error_msg('|');
            return (1);
        }
    }
    else if (flag == 0)
    {
        if (tmp->next && tmp->next->content->flag == 0 && \
                tmp->next->content->cmdline[0] == NULL)
        {
            syntax_error_msg(';');
            return (1);
        }
    }
    return (0);
}

int pipe_error_check(t_data *data)
{
    t_m_list    *tmp;
    t_cmd       *cmd;

    tmp = data->lstlast;
    while (tmp)
    {
        cmd = tmp->content;
        if (cmd->flag)
        {
            if (pipe_error_check2(tmp, 1))
                return (1);
        }
        else if (cmd->flag == 0)
        {
            if (pipe_error_check2(tmp, 0))
                return (1);
        }
        tmp = tmp->next;
    }
    return (0);
}

int	two_time_error(char *str)
{
	while (*str)
	{
		if (*str == ';')
		{
			if (*(str+ 1) != '\0' && *(str + 1) == ';')
			{
				syntax_error_msg(';');
				return (1);
			}
		}
		else if (*str == '|')
		{
			if (*(str + 1) != '\0' && *(str + 1) == '|')
			{
				syntax_error_msg('|');
				return (1);
			}
		}
		str++;
	}
	return (0);
}

int	quote_error(char *str)
{
	int	index;
	int	single_cnt;
	int	double_cnt;

	index = 0;
	single_cnt = 0;
	double_cnt = 0;
	while (str[index])
	{
		if (str[index] == '\'')
			single_cnt++;
		else if (str[index] == '\"')
			double_cnt++;
		index++;
	}
	if (single_cnt % 2 || double_cnt % 2)
		return (1);
	return (0);
}

int	check_cmd(t_data *data)
{
	char	*str;

	str = data->cmd_set;
	if (str == NULL)
		return (1);
	if (two_time_error(str) == 1)
		return (1);
	if (quote_error(str) == 1)
	{
		error_msg("shell : quote_error\n");
		return (1);
	}
	return (0);
}
