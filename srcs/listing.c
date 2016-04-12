/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 18:52:11 by vchesnea          #+#    #+#             */
/*   Updated: 2016/04/10 16:32:00 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// static int	printout_file(t_file *file, t_query *query)
// {
// 	if (new->ent->d_name[0] == '.' && !(query->flags & F_ALL))
// 		return (0);
// 	if (query->flags & F_LIST)
// 	{
// 		print_properties(file, query);
// 		print_names(file, query);
// 	}
// 	print_filename(file, query);
// 	ft_printf("\n");
// 	return (0);
// }

// static int	follow_parent_directory(t_query *query)
// {
// 	int		n;
// 	char	*s;
//
// 	n = ft_strlen(*query->paths);
// 	s = ft_strrchr(*query->paths, '/');
// 	if (s - *query->paths == n - 1)
// 		return (1);
// 	else if (s == NULL)
// 		*query->paths = ".";
// 	else
// 		*s = '\0';
// 	return (0);
// }

// static void		sort_query(t_query *query)
// {
// 	t_dir	*prev;
// 	t_dir	*curr;
// 	t_dir	*next;
//
// 	prev = query->listing;
// 	curr = prev->next;
// 	while (curr)
// 	{
// 		if (ft_strcmp(prev, curr) > 0)
// 		{
// 			prev->next = curr->next;
// 			curr->next = prev;
// 			if (prev == query->listing)
// 				query->listing = curr;
//
// 		}
// 		prev = curr;
// 		curr = curr->next;
// 	}
// }
//                 +------------+
//                 |            v
// [abc] -> [daz] -> [bod] -> [NULL]
//            ^             |
//            +-------------+

// static void		sort_query(t_query *query)
// {
// 	t_dir	*prev;
// 	t_dir	*curr;
// 	t_dir	*next;
//
// 	prev = NULL;
// 	curr = query->listing;
// 	next = curr->next;
//
// 	while (next)
// 	{
//
// 	}
// }

static void		append_file(t_dir *dir, const char *name, struct stat *stat)
{
	t_file	*new;
	t_file	*cur;

	ft_printf("{{red}}Appending file{{eoc}} '%s'\n", name);
	if ((new = malloc(sizeof(t_file))) == NULL)
		return ;
	new->next = NULL;
	new->name = name;
	new->stats = *stat;
	new->pwuid = getpwuid(stat->st_uid);
	new->grgid = getgrgid(stat->st_gid);
	cur = dir->files;
	if (cur == NULL)
	{
		dir->files = new;
		return ;
	}
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

static t_dir	*append_directory(t_query *query, const char *path)
{
	t_dir	*new;
	t_dir	*cur;

	ft_printf("{{red}}Appending directory{{eoc}} '%s'\n", path);
	if ((new = malloc(sizeof(t_dir))) == NULL)
		return (NULL);
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

static void		search_directory(t_query *query, const char *path)
{
	t_dir			*dir;
	struct stat		stat;
	struct dirent	*ent;
	char			*join;

	path = ft_strjoin(path, is_a_directory(path) ? "" : "/");
	if ((dir = append_directory(query, path)) == NULL)
		return ;
	while ((ent = readdir(dir->temp)))
	{
		if ((!ft_strncmp(ent->d_name, ".", 1) && !(query->flags & F_ALL))
			|| !ft_strcmp(ent->d_name, ".") || !ft_strcmp(ent->d_name, ".."))
			continue ;
		join = ft_strjoin(path, ent->d_name);
		lstat(join, &stat);
		if (stat.st_mode & S_IFDIR && (query->flags & F_RECURSIVE))
		{
			ft_printf("%s is a directory\n", join);
			search_directory(query, join);
			continue ;
		}
		append_file(dir, ent->d_name, &stat);
		ft_strdel(&join);
	}
	ft_strdel((char**)&path);
	closedir(dir->temp);
}

void			process_query(t_query *query)
{
	struct stat	stats;
	const char	*path;
	t_dir		*dir;

	if ((dir = append_directory(query, ".")) == NULL)
		return ;
	while (query->numpaths--)
	{
		path = query->paths[query->numpaths];
		if (stat(path, &stats))
			ft_printf("%s: %s: %s\n", query->exec, path, strerror(errno));
		else
		{
			if (!(stats.st_mode & S_IFDIR))
			{
				append_file(dir, strip_leading(path), &stats);
				continue ;
			}
			search_directory(query, path);
		}
	}
	query->grup_pad = 10;
	query->name_pad = 15;
	query->link_pad = 5;
	return (printout_listing(query));
}
