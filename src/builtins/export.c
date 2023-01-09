/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:24:00 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/06 17:09:03 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "helpers.h"

static void		ft_declare_x(char **args);
static t_bool	valid_identifier(char *name);

int	ft_export(char	**args)
{
	int		exit_status;
	char	**env_var;
	char	*err_msg;

	exit_status = EXIT_SUCCESS;
	ft_declare_x(args);
	while (*(++args))
	{
		if (valid_identifier(*args))
		{
			env_var = ft_split(*args, '=');
			ft_setenv(env_var[0], env_var[1]);
			free_strtab(env_var);
		}
		else
		{
			err_msg = "`arg': not a valid identifier";
			err_msg = str_replace(err_msg, "arg", *args);
			msh_error("export", err_msg, 0);
			free(err_msg);
			exit_status = EXIT_FAILURE;
		}
	}
	return (exit_status);
}

static t_bool	valid_identifier(char *name)
{
	int		idx;
	t_bool	valid;

	idx = 0;
	valid = FALSE;
	if (ft_isalpha(name[idx]) || name[idx] == '_')
		valid = TRUE;
	while (name[idx] && valid)
	{
		if (name[idx] == '=')
			return (valid);
		if (!ft_isalnum(name[idx]) && name[idx] != '_')
			return (FALSE);
		idx++;
	}
	return (valid);
}

static void	ft_declare_x(char **args)
{
	t_list	*envl;
	size_t	size;

	(void) args;
	size = strtab_size(args);
	if (size == 1)
	{
		envl = *get_envl();
		while (envl)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putendl_fd(envl->content, STDOUT_FILENO);
			envl = envl->next;
		}
	}
}
