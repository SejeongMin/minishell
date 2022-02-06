/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semin <semin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:45:17 by semin             #+#    #+#             */
/*   Updated: 2022/02/06 23:45:43 by soum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../Libft/libft.h"

int	get_keylen(char *str)
{
	int	ret;

	ret = 0;
	while (*str && (*str != '\'' && *str != '"'))
	{
		str++;
		ret++;
	}
	return (ret);
}

char	*replace_dollar(char *str, t_env *env)
{
	char	*c;
	int		key_len;
	char	*key;
	char	*ret;
	t_env	*found_env;

	c = str;
	while (*c && *c != '$')
		c++;
	key_len = get_keylen(c + 1);
	key = ft_substr(str, c - str + 1, key_len);
	found_env = find_env(key, env);
	if (found_env)
		ret = ft_strdup(found_env->value);
	else
		ret = NULL;
	free(key);
	return (ret);
}
