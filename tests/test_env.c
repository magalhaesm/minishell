#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "builtins.h"

void	redirect_all_std(void)
{
	cr_redirect_stdout();
}

Test(builtin_env, ft_setenv, .init = redirect_all_std)
{
	ft_setenv("key1", "value1");
	ft_env(NULL);
	fflush(stdout);
	cr_assert_stdout_eq_str("key1=value1\n");
	free_environ();
}
