/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:15:37 by yde-goes          #+#    #+#             */
/*   Updated: 2022/12/29 13:25:38 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_digit_arg(char *param);
static int	get_return_code(int nbr);

int	ft_exit(char **args)
{
	size_t	i;
	int		status;

	if (!args[1])
		return (1);
	i = 1;
	while (args[i])
	{
		status = is_digit_arg(args[i]);
		if (status == 2)
		{
			msh_error("exit", "bash: numeric argument required\n", 0);
			return (status);
		}
		i++;
	}
	if (i > 2)
	{
		msh_error("exit", "bash: too many arguments\n", 0);
		return (127);
	}
	else if (args[1])
		return (get_return_code(ft_atoi(args[1])));
	return (EXIT_SUCCESS);
}

static int	is_digit_arg(char	*param)
{
	size_t	i;

	i = 0;
	if (param[0] == '-' && (ft_strlen(param) == 1))
		return (2);
	else
		i++;
	while (param[i] != '\0')
	{
		if (!ft_isdigit(param[i]))
			return (2);
		i++;
	}
	return (0);
}

static int	get_return_code(int nbr)
{
	int	status;

	if (nbr >= 0)
		status = nbr % 256;
	else
		status = 256 + (nbr % 256);
	return (status);
}