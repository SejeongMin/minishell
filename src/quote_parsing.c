/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soum <soum@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:16:34 by soum              #+#    #+#             */
/*   Updated: 2022/02/08 16:36:27 by soum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../Libft/libft.h"

void	quote_parsing(t_data *data, char *tmp)
{
	int i;
	int j;
	(void)data;

	i = 0;
	j = 0;
	while (tmp[i])
	{
		while (tmp[i] && tmp[i] != ';' && tmp[i] != '|')
		{
			if (tmp[i] == '"')
				i = ft_strchr(&tmp[i + 1], '"') - tmp;
			i++;
		}
	}
}
