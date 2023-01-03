/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 21:24:18 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/02 18:44:24 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_unset(char **args)
{
	size_t	size;

	size = strtab_size(args);
	if (size == 1)
		return (EXIT_SUCCESS);
	while (*(++args))
	{
		if (ft_strncmp(*args, "PATH", ft_strlen(*args)) == 0)
		{
			free_pathtab();
			init_pathtab();
		}
		ft_unsetenv(*args);
	}
	return (EXIT_SUCCESS);
}
