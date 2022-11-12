#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "hash_table.h"

Test(hash_table, init_table)
{
	t_table	table;

	init_table(&table);
	cr_assert(eq(table.count, 0));
	cr_assert(eq(table.capacity, 0));
	cr_assert(eq(table.type_size, sizeof(t_entry)));
	cr_assert(eq(table.data, NULL));
}

Test(hash_table, table_set)
{
	t_table	table;
	char	*key;
	char	*value;

	key = "chave";
	value = "valor";
	init_table(&table);
	cr_assert(eq(table_set(&table, key, value), TRUE), "Fail to insert");
	cr_assert(eq(table_set(&table, key, value), FALSE), "Fail to update");
}

Test(hash_table, table_get)
{
	t_table	table;
	char	*key;
	char	*value;
	char	*expected;

	key = "chave";
	expected = "valor";
	init_table(&table);
	cr_assert(eq(table_get(&table, key, &value), FALSE),
			"Failed to return false when value not found");
	table_set(&table, key, expected);
	cr_assert(eq(table_get(&table, key, &value), TRUE),
			"Failed to return false when value found");
	cr_assert(eq(str, expected, value));
}
