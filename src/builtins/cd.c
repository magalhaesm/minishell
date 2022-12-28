/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:00:09 by yde-goes          #+#    #+#             */
/*   Updated: 2022/12/28 17:22:15 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*get_valid_arg(char **args, t_bool *is_malloc);
static char	*get_parent_folder(void);

int	ft_cd(char	**args)
{
	char	*pwd;
	char	*old_pwd;
	char	*new_dir;
	t_bool	is_malloc;

	is_malloc = FALSE;
	new_dir = get_valid_arg(args, &is_malloc);
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
	if (is_malloc)
		free(new_dir);
	return (EXIT_SUCCESS);
}

static char	*get_valid_arg(char **args, t_bool *is_malloc)
{
	size_t	size;
	char	*dir_param;

	size = get_param_size(args);
	if (size > 2)
		return (NULL);
	else if (size == 1 || ft_strncmp(args[1], "~", 1) == 0)
		dir_param = ft_getenv("HOME");
	else if (ft_strncmp(args[1], ".", 1) == 0)
	{		
		if (ft_strncmp(args[1], "..", 2) == 0)
			dir_param = get_parent_folder();
		else
			dir_param = getcwd(NULL, 0);
		*is_malloc = TRUE;
	}		
	else
		dir_param = args[1];
	return (dir_param);
}

static char	*get_parent_folder(void)
{
	char	*cwd;
	char	*dir_path;
	char	**dir_list;
	size_t	get_back;

	cwd = getcwd(NULL, 0);
	dir_list = ft_split(cwd, '/');
	get_back = ft_strlen(*dir_list) - 1;
	dir_path = ft_strtrim(cwd, dir_list[get_back]);
	free_strtab(dir_list);
	free(cwd);
	return (dir_path);
}
