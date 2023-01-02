/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:24:00 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/02 11:12:52 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static t_bool	has_name_rules(char *name);
static int		ft_declare_x(char **args);
static int		valid_chr_name(int c);

int	ft_export(char	**args)
{
	size_t	size;
	char	**env_var;

	size = strtab_size(args);
	if (size == 1)
		ft_declare_x(args);
	while (*(++args))
	{
		env_var = ft_split(*args, '=');
		if (!has_name_rules(env_var[0]))
		{
			msh_error("export", "not a valid identifier", 0);
			return (EXIT_FAILURE);
		}
		ft_setenv(env_var[0], env_var[1]);
		free_strtab(env_var);
	}
	return (EXIT_SUCCESS);
}

static t_bool	has_name_rules(char *name)
{
	size_t	i;
	size_t	length;

	i = 1;
	length = ft_strlen(name);
	if (ft_isdigit(name[0]))
		return (FALSE);
	if (length > 1)
	{
		while (name[i] != '\0')
		{
			if (ft_isspace(name[i]) || !valid_chr_name(name[i]))
				return (FALSE);
			i++;
		}
	}
	return (TRUE);
}

static int	ft_declare_x(char **args)
{
	t_list	*envl;
	char	*output;

	(void) args;
	envl = *get_envl();
	while (envl)
	{
		output = ft_strjoin("declare -x ", envl->content);
		ft_putendl_fd(output, STDOUT_FILENO);
		free(output);
		envl = envl->next;
	}
	return (EXIT_SUCCESS);
}

static int	valid_chr_name(int c)
{
	if (c == '_')
		return (1);
	return (ft_isalpha(c) || ft_isdigit(c));
}
