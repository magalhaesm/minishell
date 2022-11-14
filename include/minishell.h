/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygorgsena <ygorgsena@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:23:39 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/11/14 17:33:20 by ygorgsena        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"
# include <signal.h>
# include <sys/types.h>

typedef void	t_handler(int);

void			wait_user_signals(void);
void			show_new_prompt(int sig);

#endif
