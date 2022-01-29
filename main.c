/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soum <soum@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:54:17 by soum              #+#    #+#             */
/*   Updated: 2022/01/29 18:48:58 by soum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"
#include "./Libft/libft.h"

int	main(void)
{
	t_data	data;

	init_struct(&data);
	setting_signal();
	while (1)
	{
		show_prompt(&data);
		check_cmd(&data);
		//	return (0);
		//parsing_cmd(&data);
	}
	return (0);
}
