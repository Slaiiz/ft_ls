/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 18:52:06 by vchesnea          #+#    #+#             */
/*   Updated: 2016/05/09 17:35:45 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** sort_files: Arrange the file listing by lexicographical order, OR
** by last access time order if the F_TIME flag is specified.
** I'm not especially proud of the way I shortened the code down to the
** 25 lines limit, but it's been quite a challenge nonetheless.
*/

void	sort_files(t_query *query, t_file **files)
{
	t_file	**store;
	t_file	*tmpfil;
	int		reverse;

	store = files;
	reverse = (query->flags & F_REVERSE) && 1;
	while (*files && (*files)->next)
	{
		files = store;
		while ((tmpfil = (*files)->next))
		{
			if (reverse ^ (((query->flags & F_TIME) && ((*files)->stats.T_SEC
			< tmpfil->stats.T_SEC || ((*files)->stats.T_SEC
			== tmpfil->stats.T_SEC && ((*files)->stats.T_NSEC
			< tmpfil->stats.T_NSEC || reverse)))) || (!(query->flags & F_TIME)
			&& ft_strcmp((*files)->name, tmpfil->name) > 0)))
			{
				(*files)->next = tmpfil->next;
				tmpfil->next = *files;
				*files = tmpfil;
				break ;
			}
			files = &(*files)->next;
		}
	}
}

/*
** sort_listing: Arrange the directory listing by lexicographical order.
*/

void	sort_listing(t_query *query, t_dir **listing)
{
	t_dir	**store;
	t_dir	*tmpdir;

	store = listing;
	while (*listing && (*listing)->next)
	{
		listing = store;
		while (*listing && (tmpdir = (*listing)->next))
		{
			if (ft_strcmp((*listing)->name, tmpdir->name) > 0)
			{
				(*listing)->next = tmpdir->next;
				tmpdir->next = *listing;
				*listing = tmpdir;
				break ;
			}
			listing = &(*listing)->next;
		}
	}
	tmpdir = *store;
	while (tmpdir)
	{
		sort_files(query, &tmpdir->files);
		tmpdir = tmpdir->next;
	}
}

/*
** attach_data: Must always follow a call to append_file.
** Gets the actual stuff into the file structure.
*/

void	attach_data(t_file *file, struct stat *stats, char *path)
{
	struct group	*group;
	struct passwd	*passwd;

	file->path = path;
	file->stats = *stats;
	if ((passwd = getpwuid(stats->st_uid)) != NULL)
		file->passw = ft_strdup(passwd->pw_name);
	else
		file->passw = ft_uitoa64(stats->st_uid);
	if ((group = getgrgid(stats->st_gid)) != NULL)
		file->group = ft_strdup(group->gr_name);
	else
		file->group = ft_uitoa64(stats->st_gid);
}

/*
** strip_slashes: Return the text preceeding the rightmost slashes '/'.
** Used notably for aesthetic purposes.
*/

char	*strip_slashes(char *path)
{
	char	*tmp;

	tmp = path + ft_strlen(path);
	while (--tmp >= path)
	{
		if (*tmp != '/')
			break ;
		*tmp = '\0';
	}
	return (path);
}

/*
** set_query_paddings: Take note of the longest strings ft_ls is going to have
** to print, so as to keep every information perfectly aligned.
*/

int		set_query_paddings(t_query *query)
{
	t_dir	*dir;
	t_file	*file;

	dir = query->listing;
	while (dir)
	{
		file = dir->files;
		while (file)
		{
			if (ft_nbrlen(file->stats.st_nlink, 10) > dir->link_pad)
				dir->link_pad = ft_nbrlen(file->stats.st_nlink, 10);
			if (ft_strlen(file->passw) > dir->user_pad)
				dir->user_pad = ft_strlen(file->passw);
			if (ft_strlen(file->group) > dir->grup_pad)
				dir->grup_pad = ft_strlen(file->group);
			if (ft_nbrlen(file->stats.st_size, 10) > dir->size_pad)
				dir->size_pad = ft_nbrlen(file->stats.st_size, 10);
			if (ft_strlen(file->name) > dir->name_pad)
				dir->name_pad = ft_strlen(file->name);
			file = file->next;
		}
		dir = dir->next;
	}
	return (0);
}
