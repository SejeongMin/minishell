/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semin <semin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:20:57 by semin             #+#    #+#             */
/*   Updated: 2022/02/13 21:37:08 by semin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../Libft/libft.h"

void	print_echo(t_cmd *cmd, int i, int flag)
{
	if (!cmd->cmdline[i])
	{
		printf("\n");
		return ;
	}
	printf("%s", cmd->cmdline[i++]);
	while (cmd->cmdline[i])
	{
		printf(" %s", cmd->cmdline[i]);
		i++;
	}
	if (!flag)
		printf("\n");
}

void	ft_echo(t_cmd *cmd)
{
	int	flag;
	int	i;
	int	j;

	flag = 0;
	i = 1;
	while (cmd->cmdline[i])
	{
		if (cmd->cmdline[i][0] != '-')
			break ;
		j = 1;
		while (cmd->cmdline[i][j] == 'n')
			j++;
		if (cmd->cmdline[i][j] != '\0')
			break ;
		flag = 1;
		i++;
	}
	print_echo(cmd, i, flag);
}
