#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "expansion.h"

void setup(void)
{
	extern char	**environ;

	init_environ(environ);
	ft_setenv("var1", "value1");
	ft_setenv("var2", "value2");
	ft_setenv("var3", "value3");
}

void teardown(void)
{
	free_environ();
}

Test(quotes, split_quotes, .init = setup, .fini = teardown,
		.description = "Separates the string in quotes")
{
	t_list	*list;
	char	*expected;
	char	*string;

	string = "var1'var2'\"var3\"";
	list = split_quotes(string);
	expected = list->content;
	cr_assert(eq(str, "var1", expected));
	list = list->next;
	expected = list->content;
	cr_assert(eq(str, "'var2'", expected));
	list = list->next;
	expected = list->content;
	cr_assert(eq(str, "\"var3\"", expected));
	ft_lstclear(&list, free);
}

Test(quotes, expand_quotes, .init = setup, .fini = teardown,
		.description = "Expand and remove quotes")
{
	t_list	*list;
	char	*result;
	char	*expected;
	char	*string;

	string = "$var1'$var2'\"$var3\"";
	list = split_quotes(string);
	expand_quotes(list);

	result = list->content;
	expected = ft_getenv("var1");
	cr_assert(eq(str, result, expected));

	list = list->next;
	result = list->content;
	expected = "$var2";
	cr_assert(eq(str, result, expected));

	list = list->next;
	result = list->content;
	expected = ft_getenv("var3");
	cr_assert(eq(str, result, expected));
	ft_lstclear(&list, free);
}

Test(quotes, join_quotes, .init = setup, .fini = teardown,
		.description = "Join quotes")
{
	t_list	*list;
	char	*result;
	char	*expected;
	char	*string;

	string = "$var1'$var2'\"$var3\"''\"\"";
	list = split_quotes(string);
	expand_quotes(list);
	result = join_quotes(list);
	expected = "value1$var2value3";
	cr_assert(eq(str, result, expected));
	ft_lstclear(&list, free);
}
