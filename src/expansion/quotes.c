/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 20:41:03 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/06 16:59:22 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static t_list	*slice(char *string, int *pos, char end);
static t_bool	empty_quotes(char *str);

void	unquote(t_list *list)
{
	char	*chunk;

	while (list)
	{
		chunk = list->content;
		if (empty_quotes(chunk))
		{
			free(list->content);
			list->content = ft_strdup("");
		}
		else if (chunk[0] == '"')
		{
			chunk = ft_strtrim(chunk, "\"");
			free(list->content);
			list->content = chunk;
		}
		else if (chunk[0] == '\'')
		{
			chunk = ft_strtrim(chunk, "'");
			free(list->content);
			list->content = chunk;
		}
		list = list->next;
	}
}

char	*concatenate(t_list *list)
{
	int		size;
	char	*aux;
	char	*newstr;
	t_list	*first;

	first = list;
	size = 0;
	while (list)
	{
		size += ft_strlen(list->content);
		list = list->next;
	}
	newstr = ft_calloc(sizeof(*newstr), size + 1);
	list = first;
	while (list)
	{
		aux = list->content;
		ft_strlcat(newstr, aux, size + 1);
		list = list->next;
	}
	return (newstr);
}

t_list	*split_quotes(char *str)
{
	int		init;
	int		pos;
	char	*aux;
	t_list	*chain;

	pos = 0;
	chain = NULL;
	while (str[pos])
	{
		if (str[pos] == '"')
			ft_lstadd_back(&chain, slice(str, &pos, '"'));
		else if (str[pos] == '\'')
			ft_lstadd_back(&chain, slice(str, &pos, '\''));
		else
		{
			init = pos;
			while (str[pos] && str[pos] != '\'' && str[pos] != '"')
				pos++;
			aux = ft_substr(&str[init], 0, pos - init);
			ft_lstadd_back(&chain, ft_lstnew(aux));
			pos--;
		}
		pos++;
	}
	return (chain);
}

static t_list	*slice(char *string, int *pos, char end)
{
	int	init;

	init = (*pos)++;
	while (string[*pos] != end)
		(*pos)++;
	return (ft_lstnew(ft_substr(&string[init], 0, *pos - init + 1)));
}

static t_bool	empty_quotes(char *str)
{
	char	init;

	if (str[0] == '\'' || str[0] == '"')
		init = str[0];
	else
		return (FALSE);
	if (str[1] == init && str[2] == '\0')
		return (TRUE);
	return (FALSE);
}
