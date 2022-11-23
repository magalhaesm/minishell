/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygorgsena <ygorgsena@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:05:30 by ygorgsena         #+#    #+#             */
/*   Updated: 2022/11/22 18:56:31 by ygorgsena        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include <stdio.h>
#include <ctype.h>

#include "builtins.h"

/* Testing stdout/stderr */
void	redirect_all_std(void)
{
	cr_redirect_stdout();
}

Test(builtins_echo, echo_one_arg, .init = redirect_all_std)
{
	char *input[] = {"echo", "char", NULL};

	echo(input);
	fflush(stdout);
	cr_assert_stdout_eq_str("char\n");
}

Test(builtins_echo, echo_multi_arg, .init = redirect_all_std)
{
	char *input[] = {"echo", "char", "with 'c'", NULL};

	echo(input);
	fflush(stdout);
	cr_assert_stdout_eq_str("char with 'c'\n");
}

Test(builtins_echo, echo_zero_arg, .init = redirect_all_std)
{
	char *input[] = {"echo", NULL};

	echo(input);
	fflush(stdout);
	cr_assert_stdout_eq_str("\n");
}

Test(builtins_echo, echo_n_one_arg, .init = redirect_all_std)
{
	char *input[] = {"echo", "-n", "char", NULL};

	echo(input);
	fflush(stdout);
	cr_assert_stdout_eq_str("char");
}

Test(builtins_echo, echo_n_multi_arg, .init = redirect_all_std)
{
	char *input[] = {"echo", "-n", "char", "with 'c'", NULL};

	echo(input);
	fflush(stdout);
	cr_assert_stdout_eq_str("char with 'c'");
}

Test(builtins_echo, echo_n_zero_arg, .init = redirect_all_std)
{
	char *input[] = {"echo", "-n", NULL};

	echo(input);
	fflush(stdout);
	cr_assert_stdout_eq_str("");
}
