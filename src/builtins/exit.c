/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:15:37 by yde-goes          #+#    #+#             */
/*   Updated: 2022/12/25 18:27:56 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/* 
	[EXIT CODE: 1]
	exit

	[EXIT CODE: 2]
	exit
	bash: exit: asdfa: numeric argument required

	[IT DOESNT SHUT DOWN] exit code: 127
	exit
	bash: exit: too many arguments
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

int	ft_exit(char **args)
{
	size_t	i;
	size_t	j;
	int		status;

	if (!args[1])
		exit(1);
	i = 1;
	while (args[i])
	{
		j = 0;
		// This can be a static function
		while (args[i][j] != '\0')
		{
			if (!isdigit(args[i][j]))
			{
				msh_error("bash: exit: numeric argument required\n", NULL, 0);
				return (EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	if (i > 2)
	{
		msh_error("bash: exit: too many arguments\n", NULL, 0);
		exit(127);
	}
	else if (args[1])
	{
		status = ft_atoi(args[1]);
		exit(status);
	}
	return (EXIT_SUCCESS);
}

int	main(void)
{
	char *string[] = {"exit", "127", "1456"};
	bash_exit(string);
	return (0);
}
