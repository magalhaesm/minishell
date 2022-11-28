/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 09:49:48 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/11/28 18:31:14 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "scanner.h"

void	parse(t_scanner *scanner);
t_bool	match(t_token_type type, t_scanner *scanner);
t_bool	consume(t_token_type type, t_scanner *scanner);
void	syntax_error(t_scanner *scanner);

// RULES:
t_bool	list(t_scanner *scanner);
t_bool	conditional(t_scanner *scanner);
t_bool	pipeline(t_scanner *scanner);
t_bool	null_command(t_scanner *scanner);
t_bool	command(t_scanner *scanner);
t_bool	null_subshell(t_scanner *scanner);
t_bool	subshell(t_scanner *scanner);
t_bool	simple_cmd(t_scanner *scanner);
t_bool	null_word(t_scanner *scanner);
t_bool	fcmd_prefix(t_scanner *scanner);
t_bool	cmd_prefix(t_scanner *scanner);
t_bool	null_cmd_prefix(t_scanner *scanner);
t_bool	cmd_suffix(t_scanner *scanner);
t_bool	null_cmd_suffix(t_scanner *scanner);
t_bool	redirect_list(t_scanner *scanner);
t_bool	null_redirect_list(t_scanner *scanner);
t_bool	io_redirect(t_scanner *scanner);
t_bool	io_file(t_scanner *scanner);
t_bool	io_here(t_scanner *scanner);

#endif
