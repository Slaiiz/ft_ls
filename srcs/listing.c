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
			if ((new = malloc(sizeof(t_file) * (8 + dir->size))) == NULL)
				return (1);
			if (dir->files != NULL)
			{
				ft_memcpy(new, dir->files, dir->len * sizeof(t_file));
				free(dir->files);
			}
			dir->files = new;
			dir->size += 8;
		}
		new = &dir->files[dir->len++];
		new->ent = ent;
		lstat(ent->d_name, &new->stats);
		printout_file(new, query, 0);
	}
	return (0);
}

static int	follow_parent_directory(t_query *query)
{
	int		n;
	char	*s;

	n = ft_strlen(*query->paths);
	s = ft_strrchr(*query->paths, '/');
	if (s - *query->paths == n - 1)
		return (1);
	else if (s == NULL)
		*query->paths = ".";
	else
		*s = '\0';
	return (0);
}

int			explore_paths(t_query *query)
{
	t_directory	dir;

	ft_bzero(&dir, sizeof(t_directory));
	if ((dir.dir = opendir(*query->paths)) == NULL)
	{
		if (errno == ENOTDIR && follow_parent_directory(query))
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
		return (explore_paths(query));
	}
	return (search_directory(&dir, query));
}
