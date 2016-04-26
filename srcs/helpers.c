/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers .c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 18:52:06 by vchesnea          #+#    #+#             */
/*   Updated: 2016/04/26 11:08:23 by vchesnea         ###   ########.fr       */
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
	int		correct;

	store = files;
	while ((correct = 1))
	{
		while (*files && (*files)->next)
		{
			tmpfil = (*files)->next;
			if ((ft_strcmp((*files)->name, tmpfil->name) > 0) ||
				((query->flags & F_TIME) && ((*files)->stats.st_mtimespec.tv_sec
				> tmpfil->stats.st_mtimespec.tv_sec)))
			{
				(*files)->next = tmpfil->next;
				tmpfil->next = *files;
				*files = tmpfil;
				correct = 0;
			}
			files = &(*files)->next;
		}
		if (correct)
			break ;
		files = store;
	}
}

/*
** sort_listing: Arrange the directory listing by lexicographical order.
*/

void		sort_listing(t_dir **listing)
{
	t_dir	**store;
	t_dir	*tmpdir;
	int		correct;

	store = listing;
	while ((correct = 1))
	{
		while (*listing && (*listing)->next)
		{
			tmpdir = (*listing)->next;
			if (ft_strcmp((*listing)->name, tmpdir->name) > 0)
			{
				(*listing)->next = tmpdir->next;
				tmpdir->next = *listing;
				*listing = tmpdir;
				correct = 0;
			}
			listing = &(*listing)->next;
		}
		if (correct)
			break ;
		listing = store;
	}
}

/*
** attach_data: Must always follow a call to append_file.
** Gets the actual stuff into the file structure.
*/

void		attach_data(t_file *file, struct stat *stats, char *path)
{
	struct group	*group;
	struct passwd	*passwd;

	file->path = path;
	file->stats = *stats;
	passwd = getpwuid(stats->st_uid);
	file->passw = ft_strdup(passwd->pw_name);
	group = getgrgid(stats->st_gid);
	file->group = ft_strdup(group->gr_name);
}

/*
** strip_slashes: Return the text preceeding the rightmost slashes '/'.
** Used notably for aesthetic purposes.
*/

char		*strip_slashes(char *path)
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

int			set_query_paddings(t_query *query)
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
