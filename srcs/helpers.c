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

/*
** attach_data: Follows a call to append_file.
*/

void		attach_data(t_file *file, struct stat *stats, char *path)
{
	file->path = path;
	file->stats = *stats;
	file->pwuid = malloc(sizeof(struct passwd));
	ft_memcpy(file->pwuid, getpwuid(stats->st_uid), sizeof(struct passwd));
	file->grgid = malloc(sizeof(struct group));
	ft_memcpy(file->grgid, getgrgid(stats->st_gid), sizeof(struct group));
}

/*
** strip_slashes: Return the text preceeding the rightmost slashes '/'.
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
** get_directory_blocksize: Return the number of data blocks allocated by the
** given directory.
*/

int			get_directory_blocksize(t_dir *dir)
{
	t_file	*curr;
	size_t	total;

	total = 0;
	curr = dir->files;
	while (curr != NULL)
	{
		total += curr->stats.st_blocks;
		curr = curr->next;
	}
	return (total);
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
	while (dir != NULL)
	{
		file = dir->files;
		while (file != NULL)
		{
			if (ft_nbrlen(file->stats.st_nlink, 10) > dir->link_pad)
				dir->link_pad = ft_nbrlen(file->stats.st_nlink, 10);
			if (ft_strlen(file->pwuid->pw_name) > dir->user_pad)
				dir->user_pad = ft_strlen(file->pwuid->pw_name);
			if (ft_strlen(file->grgid->gr_name) > dir->grup_pad)
				dir->grup_pad = ft_strlen(file->grgid->gr_name);
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
