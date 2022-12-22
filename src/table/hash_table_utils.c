/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 11:59:43 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/18 22:23:26 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

void	init_table(t_table *table)
{
	table->count = 0;
	table->capacity = 0;
	table->type_size = sizeof(*table->data);
	table->data = NULL;
}

t_bool	table_get(t_table *table, char *key, char **value)
{
	t_entry	*entry;

	if (table->count == 0)
		return (FALSE);
	entry = find_entry(table->data, table->capacity, key);
	if (entry->key == NULL)
		return (FALSE);
	*value = entry->value;
	return (TRUE);
}

t_bool	table_delete(t_table *table, char *key)
{
	t_entry	*entry;

	if (table->count == 0)
		return (FALSE);
	entry = find_entry(table->data, table->capacity, key);
	if (entry->key == NULL)
		return (FALSE);
	free(entry->key);
	free(entry->value);
	entry->key = NULL;
	entry->value = RIP;
	return (TRUE);
}

void	free_table(t_table *table)
{
	int		i;
	t_entry	entry;

	i = 0;
	while (i < table->capacity)
	{
		entry = table->data[i++];
		if (entry.key != NULL)
		{
			free(entry.key);
			free(entry.value);
		}
	}
	free(table->data);
}
