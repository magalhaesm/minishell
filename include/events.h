/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:23:39 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/08 19:22:53 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include <signal.h>
# include <sys/types.h>

# include "libft.h"
# include "helpers.h"

typedef void	t_handler(int);

void			wait_user_signals(void);
void			wait_child_signals(void);
void			wait_heredoc_signals(void);
void			show_new_prompt(int sig);
void			exit_heredoc(int sig);
void			exit_child(int sig);
void			heredoc_parent_sighandler(void);

#endif
