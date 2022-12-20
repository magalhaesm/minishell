/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 08:23:11 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/20 15:28:08 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>

# include "libft.h"

// ENVIRON:
void	init_environ(char **environ);
t_list	**get_envl(void);
void	free_environ(void);
char	*ft_getenv(const char *name);
int		ft_setenv(const char *name, const char *value);
int		ft_unsetenv(const char *name);

// STRING:
void	free_strtab(char **tab);

#endif
