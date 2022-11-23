/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygorgsena <ygorgsena@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:30:40 by ygorgsena         #+#    #+#             */
/*   Updated: 2022/11/23 14:34:23 by ygorgsena        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	write_output(char **word, size_t index);

/* TODO: add echo exit status: 0 */
void	echo(char	**args)
{
	if (!args[1])
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	if (args[1] && !ft_strncmp(args[1], NEW_LINE, 2))
	{
		if (!args[2])
			return ;
		write_output(args, 2);
	}
	else
	{
		write_output(args, 1);
		ft_putstr_fd("\n", 1);
	}
}

static void	write_output(char **word, size_t index)
{
	while (word && word[index + 1])
	{
		ft_printf("%s ", word[index]);
		index++;
	}
	ft_printf("%s", word[index]);
}
