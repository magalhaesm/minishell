/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:41:25 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/11/23 20:40:16 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

#define CLOSED 0
#define UNCLOSED 1
#define METACHARS "|&;()<> \t\n"

static int	string(t_scanner *self, char c);

t_token	token_word(t_scanner *self, char c)
{
	self->iter.current--;
	while (!ft_strchr(METACHARS, *self->iter.current))
	{
		c = advance(self);
		if (c == '\'' || c == '"')
		{
			if (string(self, c) == UNCLOSED)
				return (error_token("unmatched string"));
			c = *self->iter.current;
		}
	}
	return (make_token(self, TOKEN_WORD));
}

static int	string(t_scanner *self, char c)
{
	char	close;

	close = c;
	c = advance(self);
	while (c != close && !is_at_end(self))
		c = advance(self);
	if (is_at_end(self) && c != close)
		return (UNCLOSED);
	return (CLOSED);
}
