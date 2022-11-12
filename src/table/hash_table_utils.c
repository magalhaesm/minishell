/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 11:59:43 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/11/12 17:22:36 by mdias-ma         ###   ########.fr       */
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
