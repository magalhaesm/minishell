/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:00:09 by yde-goes          #+#    #+#             */
/*   Updated: 2022/12/26 18:36:39 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_cd(char	**args)
{
	size_t	size;
	char	*pwd;
	char	*new_dir;

	size = get_param_size(args);
	if (size > 2)
	{
		msh_error("cd", "too many arguments", 0);
		return (EXIT_FAILURE);
	}
	else if (size == 1)
		new_dir = ft_getenv("HOME");
	else
		new_dir = args[1];
	if (chdir(new_dir))
		msh_error("cd", NULL, 0);
	pwd = getcwd(NULL, 0);
	ft_setenv("PWD", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
