/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soum <soum@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:41:40 by soum              #+#    #+#             */
/*   Updated: 2022/01/29 18:32:43 by soum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../Libft/libft.h"

int two_time_error(char *str)
{
	int index;

	index = 0;
	while (str[index])
	{
		if (str[index] == ';')
		{
			if (str[index + 1] != '\0' && str[index + 1] == ';')
				return (1);
		}
		else if (str[index] == '|')
		{
			if (str[index + 1] != '\0' && str[index + 1] == '|')
				return (1);
		}
		index++;
	}
	return (0);
}

int	check_cmd(t_data *data)
{
	char *str = data->cmd_set;
	if (two_time_error(str) == 1)
		error_msg("shell : syntax error near unexpected token\n");
	return (0);
}
