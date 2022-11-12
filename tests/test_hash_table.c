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
