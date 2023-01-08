/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_func.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:23:39 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/08 15:03:26 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_FUNC_H
# define SIG_FUNC_H

# include <signal.h>
# include <sys/types.h>

# include "libft.h"
# include "helpers.h"

typedef void	t_handler(int);

void			wait_user_signals(void);
void			wait_heredoc_signals(void);
void			show_new_prompt(int sig);
void			exit_heredoc(int sig);
void			heredoc_parent_sighandler(void);

#endif
