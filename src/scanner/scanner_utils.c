/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:36:07 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/11/22 18:00:02 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

t_token	make_token(const t_scanner *self, t_token_type type)
{
	t_token	token;

	token.type = type;
	token.start = self->iter.start;
	token.length = self->iter.current - self->iter.start;
	return (token);
}

t_token	error_token(const char *message)
{
	t_token	token;

	token.type = TOKEN_ERROR;
	token.start = message;
	token.length = ft_strlen(message);
	return (token);
}

t_bool	match(t_scanner *self, char expected)
{
	if (is_at_end(self))
		return (FALSE);
	if (*self->iter.current != expected)
		return (FALSE);
	advance(self);
	return (TRUE);
}

t_bool	is_at_end(t_scanner *self)
{
	return (*self->iter.current == '\0');
}

char	advance(t_scanner *self)
{
	self->iter.current++;
	return (self->iter.current[-1]);
}
