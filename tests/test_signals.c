/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_hello_world.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygorgsena <ygorgsena@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:53:47 by ygorgsena         #+#    #+#             */
/*   Updated: 2022/11/14 17:08:50 by ygorgsena        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "../include/minishell.h"

Test(test_signals, bash_sigint)
{
    signal(SIGINT, show_new_prompt);
    raise(SIGINT);
}

Test(test_signals, bash_sigquit)
{
    signal(SIGINT, SIG_IGN);
    raise(SIGQUIT);
}
