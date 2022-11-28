/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:36:07 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/11/24 15:58:09 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

t_scanner	init_scanner(const char *source)
{
	t_scanner	self;

	self.iter.start = source;
	self.iter.current = source;
	self.next = scan_token(&self);
	return (self);
}

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

t_bool	is_at_end(t_scanner *self)
{
	return (*self->iter.current == '\0');
}

char	advance(t_scanner *self)
{
	self->iter.current++;
	return (self->iter.current[-1]);
}
