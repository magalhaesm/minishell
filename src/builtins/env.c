/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:50:09 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/20 19:56:58 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(char **args)
{
	t_list	*envl;

	(void) args;
	envl = *get_envl();
	while (envl)
	{
		ft_putendl_fd(envl->content, STDOUT_FILENO);
		envl = envl->next;
	}
	return (EXIT_SUCCESS);
}
