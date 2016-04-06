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

// static int	list_files(const char *path, t_query *query)
// {
// 	return (0);
// }

// static int	search_directory(t_directory *dir, t_query *query)
// {
// 	struct dirent	*ent;
// 	t_file			*new;
//
// 	while ((ent = readdir(dir->dir)) != NULL)
// 	{
// 		if (dir->len + 1 > dir->size)
// 		{
// 			if ((new = malloc(sizeof(t_file) * (8 + dir->size))) == NULL)
// 				return (1);
// 			if (dir->files != NULL)
// 			{
// 				ft_memcpy(new, dir->files, dir->len * sizeof(t_file));
// 				free(dir->files);
// 			}
// 			dir->files = new;
// 			dir->size += 8;
// 		}
// 		new = &dir->files[dir->len++];
// 		new->ent = ent;
// 		new->group = getgrgid(new->stats.st_gid);
// 		lstat(ent->d_name, &new->stats);
// 		printout_file(new, query);
// 	}
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

// int			explore_paths(t_query *query)
// {
// 	t_directory	dir;
//
// 	ft_bzero(&dir, sizeof(t_directory));
// 	if ((dir.dir = opendir(*query->paths)) == NULL)
// 	{
// 		if (errno == ENOTDIR && follow_parent_directory(query))
// 		{
// 			ft_printf("%s: %s: %s\n", query->exec,
// 				*query->paths, strerror(errno));
// 			return (1);
// 		}
// 		else if (errno == ENOENT)
// 		{
// 			ft_printf("%s: %s: %s\n", query->exec,
// 				*query->paths, strerror(errno));
// 			return (1);
// 		}
// 		return (explore_paths(query));
// 	}
// 	return (search_directory(&dir, query));
// }

static int	is_a_directory(const char *path)
{
	return (path[ft_strlen(path) - 1] == '/');
}

static void	append_file(t_query *query, const char *path, struct stat *stat)
{
	t_file	*new;
	t_file	*cur;

	ft_printf("Appending file '%s'\n", path);
	if ((new = malloc(sizeof(t_file))) == NULL)
		return ;
	new->next = NULL;
	new->stat = *stat;
	new->pwuid = getpwuid(stat->st_uid);
	new->grgid = getgrgid(stat->st_gid);
	cur = query->listing;
	if (cur == NULL)
	{
		query->listing = new;
		return ;
	}
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

static void	search_directory(t_query *query, DIR *dir, const char *path)
{
	struct stat		stat;
	struct dirent	*ent;
	DIR				*new;
	char			*join;

	path = ft_strjoin(path, is_a_directory(path) ? "" : "/");
	while ((ent = readdir(dir)))
	{
		if (!ft_strcmp(ent->d_name, ".") || !ft_strcmp(ent->d_name, ".."))
			continue ;
		join = ft_strjoin(path, ent->d_name);
		lstat(join, &stat);
		if (stat.st_mode & S_IFDIR && (query->flags & F_RECURSIVE))
		{
			ft_printf("%s is a directory\n", join);
			search_directory(query, opendir(join), join);
			continue ;
		}
		append_file(query, join, &stat);
		ft_strdel(&join);
	}
	ft_strdel((char**)&path);
	closedir(dir);
}

void		process_query(t_query *query)
{
	struct stat	stat;
	DIR			*dir;
	const char	*path;

	path = ".";
	while (query->numpaths--)
	{
		if (query->paths != NULL)
			path = query->paths[query->numpaths];
		if ((dir = opendir(path)) == NULL)
		{
			if ((errno == ENOTDIR && is_a_directory(path)) || errno == ENOENT)
				ft_printf("%s: %s: %s\n", query->exec, path, strerror(errno));
			else
			{
				lstat(path, &stat);
				append_file(query, path, &stat);
			}
			continue ;
		}
		search_directory(query, dir, path);
	}
}
