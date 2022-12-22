/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:10:17 by yde-goes          #+#    #+#             */
/*   Updated: 2022/12/22 15:31:30 by yde-goes         ###   ########.fr       */
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
