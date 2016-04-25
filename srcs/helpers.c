/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers .c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchesnea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 18:52:06 by vchesnea          #+#    #+#             */
/*   Updated: 2016/04/20 16:01:26 by vchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_listing_by_name(t_dir **listing)
{
	t_dir	*tmpdir;
	t_file	**files;
	t_file	*tmpfil;

	while (*listing && *listing->next)
	{
		if (ft_strcmp(*listing->name, *listing->next->name) > 0)
		{
			// tmpdir = *listing->next->next;
			// *listing->next->next = *listing;
			// *listing->next = tmpdir;
			tmpdir = *listing->next->next;
			*listing->next->next = *listing;

		}
	}
}

void	sort_listing_by_date(t_dir **listing)
{

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
	passwd = getpwuid(stats->st_uid);
	file->passw = ft_strdup(passwd->pw_name);
	group = getgrgid(stats->st_gid);
	file->group = ft_strdup(group->gr_name);
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
