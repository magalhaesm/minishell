/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:15:37 by yde-goes          #+#    #+#             */
/*   Updated: 2022/12/27 11:54:24 by yde-goes         ###   ########.fr       */
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

#include "builtins.h"

int	ft_exit(char **args)
{
	return (EXIT_SUCCESS);
}
