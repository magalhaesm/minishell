/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:30:40 by ygorgsena         #+#    #+#             */
/*   Updated: 2022/12/20 18:49:20 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	write_output(char **word, size_t index);

int	ft_echo(char	**args)
{
	if (!args[1])
	{
		ft_putstr_fd("\n", 1);
		return (EXIT_SUCCESS);
	}
	if (args[1] && !ft_strncmp(args[1], NEW_LINE, 2))
	{
		if (!args[2])
			return (EXIT_SUCCESS);
		write_output(args, 2);
	}
	else
	{
		write_output(args, 1);
		ft_putstr_fd("\n", 1);
	}
	return (EXIT_SUCCESS);
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
