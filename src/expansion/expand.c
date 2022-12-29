/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:17:34 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/29 13:24:54 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"
#include "expansion.h"

static char	*find_key(char *str);

char	**expand(char **cmdtab)
{
	int		str;
	t_list	*list;

	str = 0;
	while (cmdtab[str])
	{
		list = split_quotes(cmdtab[str]);
		free(cmdtab[str]);
		parameter_expansion(list);
		cmdtab[str] = concatenate(list);
		ft_lstclear(&list, free);
		str++;
	}
	return (cmdtab);
}

char	*variable_expansion(char *string)
{
	char	*newstr;
	char	*key;
	char	*value;

	string = ft_strdup(string);
	newstr = string;
	while (TRUE)
	{
		key = find_key(string);
		if (key)
		{
			value = ft_getenv(&key[1]);
			if (!value)
				value = "";
			newstr = str_replace(string, key, value);
			free(key);
			free(string);
			string = newstr;
		}
		else
			break ;
	}
	return (newstr);
}

static char	*find_key(char *str)
{
	int	ini;
	int	pos;

	ini = 0;
	pos = 0;
	while (str[pos])
	{
		if (str[pos] == '$')
		{
			ini = pos++;
			while (str[pos] && (ft_isalnum(str[pos]) || str[pos] == '_'))
				pos++;
			return (ft_substr(str, ini, pos - ini));
		}
		else
			pos++;
	}
	return (NULL);
}
