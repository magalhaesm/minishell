/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygorgsena <ygorgsena@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:53:47 by ygorgsena         #+#    #+#             */
/*   Updated: 2022/11/15 09:55:11 by ygorgsena        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "minishell.h"

Test(test_signals, bash_sigint)
{
    signal(SIGINT, show_new_prompt);
    raise(SIGINT);
}

Test(test_signals, bash_sigquit)
{
    signal(SIGQUIT, SIG_IGN);
    raise(SIGQUIT);
}
