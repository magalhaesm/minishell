/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:18:06 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/02 14:54:05 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"
#include "hash_table.h"

static t_table	*get_pathtab(void);
static char		*get_abspath(char *argv);

void	init_pathtab(void)
{
	t_table	*pathtab;

	pathtab = get_pathtab();
	init_table(pathtab);
}

char	*search_path(char *execfile)
{
	char	*path;
	t_table	*pathtab;

	if (execfile[0] == '.' || execfile[0] == 0)
		return (NULL);
	pathtab = get_pathtab();
	if (table_get(pathtab, execfile, &path))
		return (ft_strdup(path));
	path = get_abspath(execfile);
	if (path && table_set(pathtab, execfile, path))
		return (path);
	return (NULL);
}

static t_table	*get_pathtab(void)
{
	static t_table	pathtab;

	return (&pathtab);
}

static char	*get_abspath(char *execfile)
{
	int		path;
	char	*bin;
	char	*fullpath;
	char	**syspath;

	path = 0;
	bin = ft_getenv("PATH");
	if (bin == NULL)
		bin = "";
	syspath = ft_split(bin, ':');
	bin = ft_strjoin("/", execfile);
	while (syspath[path])
	{
		fullpath = ft_strjoin(syspath[path++], bin);
		if (access(fullpath, F_OK) == 0)
		{
			free(bin);
			free_strtab(syspath);
			return (fullpath);
		}
		free(fullpath);
	}
	free(bin);
	free_strtab(syspath);
	return (NULL);
}

void	free_pathtab(void)
{
	t_table	*pathtab;

	pathtab = get_pathtab();
	free_table(pathtab);
}
