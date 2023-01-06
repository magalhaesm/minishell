/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:17:34 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/06 16:37:24 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"
#include "expansion.h"
#include "libft.h"
#include "exec.h"

static t_list	*find_key(char *str);
static char		*get_value(char *key);
static t_bool	check_pattern(t_list *list);

char	**expand(char **cmdtab)
{
	int		str;
	t_bool	glob;
	t_list	*list;
	t_list	*cmdlist;

	str = 0;
	list = NULL;
	cmdlist = NULL;
	while (cmdtab[str])
	{
		list = split_quotes(cmdtab[str]);
		glob = check_pattern(list);
		parameter_expansion(list);
		unquote(list);
		ft_lstadd_back(&cmdlist, pathname_expansion(list, glob));
		ft_lstclear(&list, free);
		str++;
	}
	return (table(cmdlist));
}

static t_bool	check_pattern(t_list *list)
{
	return (has_pattern(list, '*') || has_pattern(list, '?'));
}

char	*variable_expansion(char *string)
{
	char	*key;
	char	*value;
	char	*newstr;
	t_list	*aux;
	t_list	*list;

	string = ft_strdup(string);
	newstr = string;
	list = find_key(string);
	aux = list;
	while (aux)
	{
		key = aux->content;
		value = get_value(key);
		newstr = str_replace(string, key, value);
		free(string);
		string = newstr;
		aux = aux->next;
	}
	ft_lstclear(&list, free);
	return (newstr);
}

static char	*get_value(char *key)
{
	static char	status[4];
	char		*value;

	if (key[1] == '?')
	{
		value = ft_itoa(*get_exit_status());
		ft_strlcpy(status, value, 4);
		free(value);
		return (status);
	}
	value = ft_getenv(&key[1]);
	if (!value)
		value = "";
	return (value);
}

static t_list	*find_key(char *str)
{
	int		ini;
	int		pos;
	t_list	*lst;

	ini = 0;
	pos = 0;
	lst = NULL;
	while (str[pos])
	{
		if (str[pos] == '$')
		{
			ini = pos++;
			if (str[pos] == '?')
				ft_lstadd_back(&lst, ft_lstnew(ft_strdup("$?")));
			else if (ft_isalpha(str[pos]) || str[pos] == '_')
			{
				while (str[pos] && (ft_isalnum(str[pos]) || str[pos] == '_'))
					pos++;
				ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, ini, pos - ini)));
			}
		}
		else
			pos++;
	}
	return (lst);
}
