/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 21:24:18 by yde-goes          #+#    #+#             */
/*   Updated: 2022/12/23 16:34:02 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
	
int	ft_unset(char **args)
{
	size_t	size;

	size = get_param_size(args);
	if (size == 1)
		return (EXIT_SUCCESS);
	while (*(++args))
		ft_unsetenv(*args);
	return (EXIT_SUCCESS);
}
