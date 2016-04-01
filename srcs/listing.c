/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 18:52:11 by vchesnea          #+#    #+#             */
/*   Updated: 2016/04/01 18:52:12 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	printout_file(t_file *file, t_query *query, int padding)
{
	if (query->flags & F_LIST)
		print_access(file, query);
	print_filename(file, query, padding);
	return (0);
}

static int	list_files(const char *path, t_query *query)
{
	return (0);
}

static int	search_directory(t_directory *dir, t_query *query)
{
	struct dirent	*ent;
	t_file			*new;

	while ((ent = readdir(dir->dir)) != NULL)
	{
		if (dir->len + 1 > dir->size)
		{
			if ((new = malloc(sizeof(t_file) * (INC_FACTOR + dir->size))))
			if (dir->files != NULL)
			{
				ft_memcpy(new, dir->files, dir->len * sizeof(t_file));
				free(dir->files);
			}
			dir->files = new;
			dir->size += INC_FACTOR;
		}
		new = &dir->files[dir->len++];
		new->ent = ent;
		lstat(ent->d_name, &new->stats);
		printout_file(new, query, 0);
	}
	return (0);
}

int			explore_paths(t_query *query)
{
	char			*s;
	t_directory		dir;

	if ((dir.dir = opendir(*query->paths)) == NULL)
	{
		s = strrchr(*query->paths, '/');
		if (errno == ENOTDIR && s && s[1] == '\0')
		{
			ft_printf("%s: %s: %s\n", query->exec,
				*query->paths, strerror(errno));
			return (1);
		}
		else if (errno == ENOENT)
		{
			ft_printf("%s: %s: %s\n", query->exec,
				*query->paths, strerror(errno));
			return (1);
		}
		if (s != NULL)
		{
			*s = '\0';
			*query->paths = s - 1;
		}
		return (explore_paths(query));
	}
	dir.size = 0;
	return (search_directory(&dir, query));
}
