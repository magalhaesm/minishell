/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:40:01 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/11/11 23:15:56 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

typedef struct s_entry
{
	char	*key;
	char	*value;
}	t_entry;

typedef struct s_table
{
	int		count;
	int		capacity;
	int		type_size;
	t_entry	*data;
}	t_table;

void	init_table(t_table *table);

#endif
