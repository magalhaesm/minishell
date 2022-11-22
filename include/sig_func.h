/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_func.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygorgsena <ygorgsena@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:21:10 by ygorgsena         #+#    #+#             */
/*   Updated: 2022/11/22 17:25:42 by ygorgsena        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_FUNC_H
# define SIG_FUNC_H

# include <signal.h>
# include <sys/types.h>

# include "libft.h"

typedef void	t_handler(int);

void			wait_user_signals(void);
void			show_new_prompt(int sig);

#endif