/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:50:16 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/21 16:14:54 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static t_bool	check_word(char *name, int start, int length, char *rest);

t_builtin	builtin_pool(char *name)
{
	if (name[0] == 'c' && check_word(name, 1, 1, "d"))
		return (NULL);
	else if (name[0] == 'e')
	{
		if (name[1] == 'c' && check_word(name, 2, 2, "ho"))
			return (ft_echo);
		else if (name[1] == 'n' && check_word(name, 2, 1, "v"))
			return (ft_env);
		else if (name[1] == 'x')
		{
			if (name[2] == 'i' && check_word(name, 3, 1, "t"))
				return (NULL);
			if (name[2] == 'p' && check_word(name, 3, 3, "ort"))
				return (NULL);
		}
	}
	else if (name[0] == 'p' && check_word(name, 1, 2, "wd"))
		return (NULL);
	else if (name[0] == 'u' && check_word(name, 1, 4, "nset"))
		return (NULL);
	return (NULL);
}

static t_bool	check_word(char *name, int start, int length, char *rest)
{
	return (ft_memcmp(name + start, rest, length + 1) == 0);
}
