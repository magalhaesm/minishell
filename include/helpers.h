/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 08:23:11 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/27 20:27:57 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

# include <stdio.h>
# include <string.h>

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

/* Initialize the internal path table */
void	init_pathtab(void);

/* Looks up the path of an executable in the internal hash table and returns it.
   If it's not in the table, then look it up in the PATH and add it.
   Returns a copy of the path that must be freed by the user. */
char	*search_path(char *execfile);

/* Free the internal path table */
void	free_pathtab(void);

/* Return the length of a string table */
size_t	strtab_size(char **tab);

/* Free a string table */
void	free_strtab(char **tab);

/* Displays error on standard error.
   `name` is the location of the error. `msg` is a custom message.
   `error` is a code defined in errno.h.
   For standard Unix messaging, let `msg` be NULL and use `error`
   If both msg and error are null, the message will be the last error
   encountered during a system call or library function. */
void	msh_error(char *name, char *msg, int error);

/* Protected fork. On success, return the child's pid. On error, send
   a message to standard error and return -1. */
int		pfork(void);

/* Count occurrences of a word */
int		wordcount(char *str, char *word);

/* Replace all occurrences of a word */
char	*str_replace(char *str, char *oldw, char *neww);

#endif
