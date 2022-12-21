/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:19:14 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/20 15:41:15 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

void	init_environ(char **environ)
{
	int		var;
	t_list	**envl;
	t_list	*new_node;

	var = 0;
	envl = get_envl();
	while (environ[var])
	{
		new_node = ft_lstnew(ft_strdup(environ[var]));
		ft_lstadd_back(envl, new_node);
		var++;
	}
}

t_list	**get_envl(void)
{
	static t_list	*envl;

	return (&envl);
}

void	free_environ(void)
{
	ft_lstclear(get_envl(), free);
}
