#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "builtins.h"

Test(builtin_pool, return_valid)
{
	t_builtin	expected;
	t_builtin	received;

	expected = ft_echo;
	received = builtin_pool("echo", NULL);
	cr_assert(eq(ptr, expected, received));
}

Test(builtin_pool, return_null_for_invalid)
{
	t_builtin	expected;
	t_builtin	received;

	expected = NULL;
	received = builtin_pool("nonexistent", NULL);
	cr_assert(eq(ptr, expected, received));
}
