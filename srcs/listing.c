/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 18:52:11 by vchesnea          #+#    #+#             */
/*   Updated: 2016/06/01 15:43:16 by vchesnea         ###   ########.fr       */
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
		exit(errno);
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
** This entry will expose all the files it contains.
*/

static t_dir	*append_directory(t_query *query, char *path)
{
	t_dir	*new;
	t_dir	*cur;

	if ((new = malloc(sizeof(t_dir))) == NULL)
		exit(errno);
	ft_bzero(&new->name_pad, 5 * sizeof(size_t));
	if ((new->temp = opendir(path)) == NULL)
	{
		print_error(query->exec, path, strerror(errno));
		return (NULL);
	}
	new->name = path;
	new->files = NULL;
	new->next = NULL;
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
** -
** This algorithm only implements a one-pass recursion so the results won't
** be yielded until the very last file is found. As a consequence it is not
** advised to search huge directories even if you just want a glimpse of what's
** inside. (That'd be easy but I ran out of lines ya see ...)
*/

static int		search_directory(t_query *query, char *path)
{
	struct dirent	*ent;
	t_dir			*dir;
	char			*join;
	t_file			*file;

	if ((dir = append_directory(query, ft_strjoin(path, "/"))) == NULL)
		return (1);
	while ((ent = readdir(dir->temp)))
	{
		if (!ft_strncmp(ent->d_name, ".", 1) && !(query->flags & F_ALL))
			continue ;
		if (!lstat((join = ft_strjoin(dir->name, ent->d_name)), &query->stats))
		{
			file = append_file(ent->d_name, dir);
			attach_data(file, &query->stats, join);
			if (S_ISDIR(query->stats.st_mode) && (query->flags & F_RECURSIVE)
			&& (ft_strcmp(ent->d_name, "..") && ft_strcmp(ent->d_name, ".")))
				search_directory(query, join);
		}
		else
			print_error(query->exec, join, strerror(errno));
	}
	closedir(dir->temp);
	return (0);
}

/*
** printout_listing: The function that calls each of the above.
** We skip the first dummy list element (If files were queried, it will
** contain all of them).
*/

static void		printout_listing(t_query *query)
{
	t_dir	*dir;
	int		multiple;

	dir = query->listing;
	multiple = dir->next && dir->next->next;
	if (dir->files == NULL)
		dir = dir->next;
	while (dir)
	{
		if (multiple && dir != query->listing)
		{
			dir->name[ft_strlen(dir->name) - 1] = '\0';
			ft_printf("%s:\n", dir->name);
		}
		printout_directory(query, dir);
		dir = dir->next;
		if (dir)
			ft_putchar('\n');
	}
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
		return (1);
	while (query->numpaths--)
	{
		path = *query->paths++;
		if (lstat(path, &stats))
			print_error(query->exec, path, strerror(errno));
		else if (!S_ISDIR(stats.st_mode))
		{
			file = append_file(path, dir);
			attach_data(file, &stats, ft_strdup(path));
		}
		else if (search_directory(query, path))
			return (print_error(query->exec, path, strerror(errno)));
	}
	set_query_paddings(query);
	sort_listing(query, &query->listing);
	printout_listing(query);
	return (0);
}
