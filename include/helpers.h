/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 08:23:11 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/20 16:53:05 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>

# include "libft.h"

/* Generate an internal list of variables from environ. */
void	init_environ(char **environ);

/* Get the internal list of environment variables. */
t_list	**get_envl(void);

/* Free the internal list of environment variables. */
void	free_environ(void);

/* Searches the environment list to find the environment variable name.
   Returns a pointer to the value in the environment, or NULL if there
   is no match. */
char	*ft_getenv(const char *name);

/* Adds the variable name to the environment with the value value.
   Return zero on success, or -1 on error. */
int		ft_setenv(const char *name, const char *value);

/* Deletes the variable name from the environment.
   Return zero on success, or -1 on error. */
int		ft_unsetenv(const char *name);

/* Free a string table. */
void	free_strtab(char **tab);

#endif
