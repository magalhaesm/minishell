/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 10:40:04 by yde-goes          #+#    #+#             */
/*   Updated: 2022/12/26 09:26:41 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(char **args)
{
	char	*pwd;

	(void) args;
	pwd = ft_getenv("PWD");
	if (!pwd)
		msh_error("pwd", "Environment variable doesn't exist.", 0);
	ft_printf("%s\n", pwd);
	return (EXIT_SUCCESS);
}
