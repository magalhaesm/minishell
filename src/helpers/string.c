/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 20:59:21 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/24 11:01:02 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	strtab_size(char **tab)
{
	size_t	str;

	str = 0;
	while (tab[str])
		str++;
	return (str);
}

void	free_strtab(char **tab)
{
	int	str;

	str = 0;
	if (tab == NULL)
		return ;
	while (tab[str])
		free(tab[str++]);
	free(tab);
}
