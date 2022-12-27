/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:00:09 by yde-goes          #+#    #+#             */
/*   Updated: 2022/12/27 11:22:26 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char *get_valid_arg(char **args);

int	ft_cd(char	**args)
{
	char	*pwd;
	char	*old_pwd;
	char	*new_dir;

	new_dir = get_valid_arg(args);
	if (!new_dir)
	{
		msh_error("cd", "too many arguments", 0);
		return (EXIT_FAILURE);
	}
	if (chdir(new_dir))
	{
		msh_error("cd", NULL, 0);
		return (EXIT_FAILURE);
	}
	old_pwd = ft_getenv("PWD");
	ft_setenv("OLDPWD", old_pwd);
	pwd = getcwd(NULL, 0);
	ft_setenv("PWD", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}

static char *get_valid_arg(char **args)
{
	size_t	size;
	char	*dir_param;

	size = get_param_size(args);
	if (size > 2)
		return (NULL);
	else if (size == 1)
		dir_param = ft_getenv("HOME");
	else
		dir_param = args[1];
	return (dir_param);
}
