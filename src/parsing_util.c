/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soum <soum@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:11:52 by soum              #+#    #+#             */
/*   Updated: 2022/02/07 16:18:34 by soum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../Libft/libft.h"

int	quote_index(char *cmd, char let, int *index)
{
	(*index)++;
	while (cmd[*index] && cmd[*index] != let)
		(*index)++;
	return (1);
}

char	*put_in_cmdline(char *cmd, char let, int *i)
{
	int from;
	char *cmdline;

	(*i)++;
	from = *i - 1;
	while (cmd[*i] && cmd[*i] != let)
		(*i)++;
	while (cmd[*i] && cmd[*i] != ' ')
		(*i)++;
	cmdline = (char *)malloc((*i - from + 1) *sizeof(char));
	putin(cmd, cmdline, from, (*i) + 1);
	return (cmdline);
}
