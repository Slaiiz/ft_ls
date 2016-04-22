/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 18:52:11 by vchesnea          #+#    #+#             */
/*   Updated: 2016/04/20 15:37:13 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** append_file: Add a file entry in the current directory entry.
*/

static t_file	*append_file(char *name, t_dir *dir)
{
	t_file	*new;
	t_file	*cur;

	if ((new = malloc(sizeof(t_file))) == NULL)
		return (NULL);
	new->next = NULL;
	new->name = ft_strdup(name);
	cur = dir->files;
	if (cur == NULL)
	{
		dir->files = new;
		return (new);
	}
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	return (new);
}

/*
** append_directory: Add a directory entry in the listing.
*/

static t_dir	*append_directory(t_query *query, char *path)
{
	t_dir	*new;
	t_dir	*cur;

	if ((new = malloc(sizeof(t_dir))) == NULL)
		return (NULL);
	ft_bzero(&new->name_pad, 5 * sizeof(size_t));
	if ((new->temp = opendir(path)) == NULL)
	{
		ft_printf("%s: %s: %s\n", query->exec, path, strerror(errno));
		return (NULL);
	}
	new->files = NULL;
	new->next = NULL;
	new->name = path;
	cur = query->listing;
	if (cur == NULL)
	{
		query->listing = new;
		return (new);
	}
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	return (new);
}

/*
** search_directory: Recursively collect data on files contained in the current
** working path, each directory encountered adds an entry in the listing.
** The first step in the function is ensuring the given path ends with a slash.
*/

static int		search_directory(t_query *query, char *path)
{
	t_dir			*dir;
	struct dirent	*ent;
	char			*join;
	t_file			*file;
	struct stat		stats;

	path = ft_strjoin(path, path[ft_strlen(path) - 1] == '/' ? "" : "/");
	if ((dir = append_directory(query, path)) == NULL)
		return (1);
	while ((ent = readdir(dir->temp)))
	{
		if ((!ft_strncmp(ent->d_name, ".", 1) || !ft_strcmp(ent->d_name, ".."))
			&& !(query->flags & F_ALL))
			continue;
		join = ft_strjoin(path, ent->d_name);
		lstat(join, &stats);
		if (S_ISDIR(stats.st_mode) && (query->flags & F_RECURSIVE))
			search_directory(query, join);
		file = append_file(ent->d_name, dir);
		attach_data(file, &stats, join);
	}
	closedir(dir->temp);
	return (0);
}

/*
** process_query: Where the magic is. First create a dummy directory pointing
** at the current working path. In the event a file is queried, it is assumed
** to be contained in that directory. For each query, if it is a directory,
** call search_directory. If it is not, attach it to the dummy directory.
*/

int				process_query(t_query *query)
{
	t_dir		*dir;
	t_file		*file;
	char		*path;
	struct stat	stats;

	if ((dir = append_directory(query, ft_strdup("."))) == NULL)
		return (1) ;
	while (query->numpaths--)
	{
		path = *query->paths++;
		if (lstat(path, &stats))
			ft_printf("%s: %s: %s\n", query->exec, path, strerror(errno));
		else if (S_ISDIR(stats.st_mode))
		{
			if (search_directory(query, path))
				return (1);
		}
		else
		{
			if ((file = append_file(path, dir)) == NULL)
				return (1);
			attach_data(file, &stats, ft_strdup(path));
		}
	}
	return (set_query_paddings(query));
}
