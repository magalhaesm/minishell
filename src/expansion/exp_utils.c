/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:36:45 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/06 16:40:03 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

t_list	*pathname_expansion(t_list *chunks, t_bool glob)
{
	t_list	*list;
	char	*pattern;

	pattern = concatenate(chunks);
	if (glob)
	{
		list = list_matches(pattern);
		if (list)
		{
			free(pattern);
			return (list);
		}
	}
	return (ft_lstnew(pattern));
}

void	parameter_expansion(t_list *list)
{
	char	*aux;

	while (list)
	{
		aux = list->content;
		if (aux[0] != '\'')
		{
			aux = variable_expansion(list->content);
			free(list->content);
			list->content = aux;
		}
		list = list->next;
	}
}

t_list	*list_matches(char *pattern)
{
	t_list			*matches;
	DIR				*dp;
	char			dirbuf[PATH_MAX];
	struct dirent	*dir;

	matches = NULL;
	getcwd(dirbuf, PATH_MAX);
	dp = opendir(dirbuf);
	dir = readdir(dp);
	while (dir != NULL)
	{
		dir = readdir(dp);
		if (dir && dir->d_type == DT_REG && is_match(dir->d_name, pattern))
			ft_lstadd_back(&matches, ft_lstnew(ft_strdup(dir->d_name)));
	}
	closedir(dp);
	return (matches);
}

t_bool	has_pattern(t_list *list, char chr)
{
	char	*aux;
	t_bool	pattern;

	pattern = FALSE;
	while (list)
	{
		aux = list->content;
		if (ft_strchr(aux, chr))
		{
			if (!ft_strchr(aux, '"') && !ft_strchr(aux, '\''))
				pattern = TRUE;
		}
		list = list->next;
	}
	return (pattern);
}

char	**table(t_list *list)
{
	int		index;
	char	**argv;
	t_list	*aux;

	argv = ft_calloc(sizeof(char *), ft_lstsize(list) + 1);
	index = 0;
	while (list)
	{
		aux = list;
		argv[index++] = aux->content;
		list = list->next;
		free(aux);
	}
	return (argv);
}
