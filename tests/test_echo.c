/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:10:17 by yde-goes          #+#    #+#             */
/*   Updated: 2022/12/22 15:31:40 by yde-goes         ###   ########.fr       */
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

	ft_echo(input);
	fflush(stdout);
	cr_assert_stdout_eq_str("char\n");
}

Test(builtins_echo, echo_multi_arg, .init = redirect_all_std)
{
	char *input[] = {"echo", "char", "with 'c'", NULL};

	ft_echo(input);
	fflush(stdout);
	cr_assert_stdout_eq_str("char with 'c'\n");
}

Test(builtins_echo, echo_zero_arg, .init = redirect_all_std)
{
	char *input[] = {"echo", NULL};

	ft_echo(input);
	fflush(stdout);
	cr_assert_stdout_eq_str("\n");
}

Test(builtins_echo, echo_n_one_arg, .init = redirect_all_std)
{
	char *input[] = {"echo", "-n", "char", NULL};

	ft_echo(input);
	fflush(stdout);
	cr_assert_stdout_eq_str("char");
}

Test(builtins_echo, echo_n_multi_arg, .init = redirect_all_std)
{
	char *input[] = {"echo", "-n", "char", "with 'c'", NULL};

	ft_echo(input);
	fflush(stdout);
	cr_assert_stdout_eq_str("char with 'c'");
}

Test(builtins_echo, echo_n_zero_arg, .init = redirect_all_std)
{
	char *input[] = {"echo", "-n", NULL};

	ft_echo(input);
	fflush(stdout);
	cr_assert_stdout_eq_str("");
}
