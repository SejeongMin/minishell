/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semin <semin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:45:42 by soum              #+#    #+#             */
/*   Updated: 2022/02/14 01:42:13 by semin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../Libft/libft.h"

void	error_msg(char *str)
{
	printf("%s", str);
	g_status = 258;
}

int	syntax_error_msg(char let)
{
	printf("minishell : syntax error near unexpected token '%c'\n", let);
	g_status = 258;
	return (1);
}
