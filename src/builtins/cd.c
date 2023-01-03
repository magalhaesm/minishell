/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:00:09 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/01 19:15:34 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*get_valid_arg(char **args);
static char	*handle_special_cd(char **args);

int	ft_cd(char	**args)
{
	char	pwd[PATH_MAX];
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
	getcwd(pwd, PATH_MAX);
	ft_setenv("PWD", pwd);
	return (EXIT_SUCCESS);
}

static char	*get_valid_arg(char **args)
{
	size_t		size;
	char		*dir_param;

	size = strtab_size(args);
	if (size > 2)
		return (NULL);
	else if (size == 1)
		return (ft_getenv("HOME"));
	dir_param = handle_special_cd(args);
	if (!dir_param)
		dir_param = args[1];
	return (dir_param);
}

static char	*handle_special_cd(char **args)
{
	static char	pwd[PATH_MAX];
	size_t		arg_len;
	char		*dir_param;

	arg_len = ft_strlen(args[1]);
	dir_param = NULL;
	if (arg_len == 1 && ft_strncmp(args[1], "~", 1) == 0)
		dir_param = ft_getenv("HOME");
	else if (arg_len == 1 && ft_strncmp(args[1], ".", 1) == 0)
	{
		getcwd(pwd, PATH_MAX);
		return (pwd);
	}			
	else if (arg_len == 2 && ft_strncmp(args[1], "..", 2) == 0)
		dir_param = "..";
	return (dir_param);
}
